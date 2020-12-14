#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "DataManipulation.h"
#include "neuralnetwork.h"

/*
 *A File is created at the path: filename where we want to save the network
 * with all the weights, biases and info about the orinal network
 */

void save(struct NeuralNetwork network, char *filename)
{
	FILE *fp;

	fp = fopen(filename, "w");
	//stores the number of inputs"
	fprintf(fp, "%d\n", network.nbr_inputs);

	//stores the number of layers
	fprintf(fp, "%d\n", network.nbr_layers);


	for (Layer *i = network.layer; i < network.layer + network.nbr_layers; i++)
	{
		//stores the number of neuronnes for each layers
		fprintf(fp, "%d\n", i->nbr_neuronnes);
	}
	

	for(int i = 0; i < network.nbr_layers; i++)
	{
		Layer *layer = network.layer + i;


		for(int j = 0; j < layer->nbr_neuronnes; j++)
		{
			Neuronne *neurone = (layer->neuronne) + j;

			// ecrit le biais
			fprintf(fp, "%f\n", neurone->biais);
			for(int k = 0; k < neurone->nbr_poids; k++)
			{
				//ecris le poids
				double *weight = (neurone->weigth) + k;
				fprintf(fp, "%f\n", *weight);
			}
		}
	}

	fclose(fp);
}

struct NeuralNetwork load(char *filename)
{
	FILE *fp;
	char * line = NULL;
	size_t len = 0;
	size_t read;

	fp = fopen(filename, "r");

	if (fp == NULL)
		exit(EXIT_FAILURE);
	int nbr_inputs;
	int nbr_layer = 1;
	double biais_du_neurone;

	read = getline(&line, &len, fp);
	line = strtok(line, "\n");
	read -= 1;
	nbr_inputs = strtol(line, NULL, 10);

	read = getline(&line, &len, fp);
	line = strtok(line, "\n");
	read -= 1;
	nbr_layer = strtol(line, NULL, 10);

	int layers[nbr_layer];
	for (int i = 0; i < nbr_layer; i++)
	{
		read = getline(&line, &len, fp);
		line = strtok(line, "\n");
		read -= 1;
		layers[i] = strtol(line, NULL, 10);
	}
	Layer *layer = malloc(nbr_layer * sizeof(Layer));
	Layer *l = layer; 
	for(int i = 0; i < nbr_layer; i++)
	{
		int length;
		if(i == 0)
		{
			length = nbr_inputs;
		}
		else
		{
			length = layers[i-1];
		}
		Neuronne *neuronne = malloc(layers[i] * sizeof(Neuronne));
		Neuronne *n = neuronne;

		for (int j = 0; j < layers[i]; j++)
		{
			read = getline(&line, &len, fp);
			line = strtok(line, "\n");
			read -= 1;
			char *biais = strtok(line, "\n");
			double biais_d = atof(biais);
			double *weigth = malloc(length * sizeof(double));
			double *w = weigth;
			for (int k = 0; k < length; k++)
			{
				read = getline(&line, &len, fp);
				line = strtok(line, "\n");
				read -= 1;
				char *weight_i = strtok(line, "\n");
				*w = atof(weight_i);
				w += 1;
			}
			Neuronne neuronne = {length, weigth, w, biais_d, 0, 0}; 
			*n = neuronne;
			n ++;
		}
		Layer l_i = {layers[i], neuronne, n};
		*l = l_i;
		l++;
	}
	NeuralNetwork neuralnetwork = {nbr_layer, nbr_inputs, layer, l};
	fclose(fp);
	return neuralnetwork;
}
