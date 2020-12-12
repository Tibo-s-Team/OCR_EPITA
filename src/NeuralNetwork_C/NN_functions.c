#include <stdio.h>
#include <stdlib.h>
#include "neuralnetwork.h"
#include "NN_functions.h"
#include <math.h>

double sigmoid(double x)
{
    return 1/(1 + exp(-x));
}

double sigmoidPrime(double x)
{
    return x * (1-x);
}

void feedForward(NeuralNetwork neuralnetwork, double *inputs, int len)
{
    for(int i = 0; i < neuralnetwork.nbr_layers; i++)
    {
        Layer *layer = neuralnetwork.layer +i;
        for(int j = 0; j < layer->nbr_neuronnes; j++)
        {
            Neuronne *neuronne = (layer->neuronne)+j;
            double somme = 0.0;
            int length;
            if (i == 0)
            {
                length = len;
            }
            else
            {
                length = (layer-1)->nbr_neuronnes;
            }
            for(int k = 0; k < length; k++)
            {
                double *weigth = neuronne->weigth;
                
                if(i == 0)
                {
                    somme += *(inputs + k) * (*(weigth + k));
                }
                else
                {
                    Neuronne *neuronne_precedent = (layer-1)->neuronne;
                    somme += (neuronne_precedent + k)->output * (*(weigth + k));
                }
                      
            }
            neuronne->output = sigmoid(somme + neuronne->biais); 
        }
    }
}

double* print_output(NeuralNetwork neuralnetwork)
{
    double* output = malloc((neuralnetwork.end -1)->nbr_neuronnes * sizeof(double));
    double* j = output;
    Layer *layer = neuralnetwork.end -1;
    printf("__________\n");
    for(Neuronne *i = layer->neuronne; i < layer->end; i++)
    {
        printf("%f\n", i->output);
        *j = i->output;
        j++;
    }
    return output;
}
    
void backPropagation(NeuralNetwork neuralnetwork, double waited[])
{
    for(int i = neuralnetwork.nbr_layers-1; i >= 0; i--)
    {
        Layer *layer = neuralnetwork.layer + i;
        if(i == neuralnetwork.nbr_layers-1)
        {
            for(int j = 0; j < layer->nbr_neuronnes; j++)
            {
                Neuronne *neuronne = layer->neuronne + j;
                neuronne->error = (waited[j] - neuronne->output) * sigmoidPrime(neuronne->output);
            }
        }
        else
        {
            Layer *next_layer = neuralnetwork.layer + i + 1;
            for(int j = 0; j < layer->nbr_neuronnes; j++)
            {
                double error = 0;
                for(int k = 0; k < next_layer->nbr_neuronnes; k++)
                {
                    Neuronne *neuronne = next_layer->neuronne+k;
                    error += *(neuronne->weigth + j) * neuronne->error;
                }
                Neuronne *neuronne = layer->neuronne + j;
                neuronne->error = error * sigmoidPrime(neuronne->output);
            }
        }
    }
}

void print_error(NeuralNetwork neuralnetwork)
{
    Layer *layer = neuralnetwork.end -1;
    for(Neuronne *i = layer->neuronne; i < layer->end; i++)
    {
        printf("%f \n", i->error);
    }
}

void updateWeigth(NeuralNetwork neuralnetwork, double *inputs, int len, double coeff)
{
    for(int i = 0; i < neuralnetwork.nbr_layers; i++)
    {
        Layer *layer = neuralnetwork.layer + i;
        for(int k = 0; k < layer->nbr_neuronnes; k++)
        {
            Neuronne *neuronne = layer->neuronne + k;
            double* weigth = neuronne->weigth;
            if(i == 0)
            {
                for(int j = 0; j < len; j++)
                {
                    *(weigth + j) += coeff * neuronne->error * *(inputs + j); 
                }
            }
            else
            {
                Layer *before_layer = neuralnetwork.layer + i - 1;
                for(int j = 0; j < before_layer->nbr_neuronnes; j++)
                {
                    Neuronne *before_neuronne = before_layer->neuronne + j;
                    *(weigth + j) += coeff * neuronne->error * before_neuronne->output;
                }
            }
            neuronne->biais += coeff * neuronne->error;
        }
    }
}