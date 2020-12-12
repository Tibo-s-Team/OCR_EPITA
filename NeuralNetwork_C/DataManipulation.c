#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "DataManipulation.h"

/*
 *A File is created at the path: filename where we want to save the network
 * with all the weights, biases and info about the orinal network
 */

void save(struct NeuralNetwork network, char *filename)
{
	FILE *fp;

	fp = fopen(filename, "w");
	//stores the number of inputs
	fprintf(fp, "%d\n", network.nbr_inputs);

	//stores the number of layers
	fprintf(fp, "%d\n", network.nbr_layers);

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
				fprintf(fp, "%f,", *weight);
			}
			fprintf(fp, "\n");
		}
	}

	fclose(fp);
}

/*
struct NeuralNetwork load(char *filename)
{
	FILE *fp;
	char * line = NULL;
	size_t len = 0;
	size_t read;

	fp = fopen(filename, "r");

	if (fp == NULL)
		exit(EXIT_FAILURE);
	
	int i = 0;
	int nbr_inputs;
	int nbr_layer;

	while((read = getline(&line, &len, fp)) != -1)
	{
		line = strtok_r(line, "\n");
		read -= 1;
		if (i == 0)
			nbr_inputs = strtol(line, NULL, 10);
		else if (i == 1) 
			nbr_layer = strtol(line, NULL, 10);
		else
		{
			if(i % 2 == 1)
				//biais du neurone = strtod(line, NULL, 10);
			else
			{
				char *weight = strtok(line, ",");
				while(weight != NULL)
				{
					//on donne a neurone.weight[indice] = weight
					weight = strtok(NULL, ",");
				}
			}
		}
		i++;
	}

	fclose(fp);
	//return neuralnetwork
}*/
