#include <stdio.h>
#include <stdlib.h>
#include "neuralnetwork.h"
#include "NN_functions.h"
#include <math.h>

double sigmoid(double x)
{
    return 1/(1 + exp(x));
}

void feedForward(NeuralNetwork neuralnetwork, double inputs[], int len)
{
    Layer *layer = neuralnetwork.layer;
    for(int i = 0; i < neuralnetwork.nbr_layers; i++)
    {
        for(int j = 0; j < layer->nbr_neuronnes; j++)
        {
            Neuronne *neuronne_precedent = (layer-1)->neuronne;
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
                    somme += inputs[k] * (*(weigth + k));
                }
                else
                {
                    somme += (neuronne_precedent + k)->output * (*(weigth + k));
                }
                      
            }
            neuronne->output = sigmoid(somme + neuronne->biais); 
        }
        layer += 1;
    }
}

double* print_output(NeuralNetwork neuralnetwork)
{
    double* output = malloc((neuralnetwork.end -1)->nbr_neuronnes * sizeof(double));
    double* j = output;
    Layer *layer = neuralnetwork.end -1;
    for(Neuronne *i = layer->neuronne; i < layer->end; i++)
    {
        *j = i->output;
        printf("%f \n", i->output);
        j++;
    }
    return output;
}
    