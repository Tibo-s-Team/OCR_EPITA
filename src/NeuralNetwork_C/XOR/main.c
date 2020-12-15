#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../neuralnetwork.h"
#include "../NN_functions.h"

void XORtraining(int times, NeuralNetwork neuralnetwork)
{
    double inputs[4][2] = {{1.0, 0.0}, {0.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}};
    double waited[4][1] = {{1.0}, {0.0}, {0.0}, {1.0}};
    for(int i = 0; i < times; i++)
    {
        
        for(int j = 0; j < 4; j++)
        {
            feedForward(neuralnetwork, inputs[j], 2);
            backPropagation(neuralnetwork, waited[j]);
            updateWeigth(neuralnetwork, inputs[j], 2, 0.1);
        }
    }
}

void XOR(NeuralNetwork neuralnetwork, double a, double b)
{
    double values[2] = {a, b};
    feedForward(neuralnetwork, values, 2);
    Layer *layer = neuralnetwork.end -1;
    for(Neuronne *i = layer->neuronne; i < layer->end; i++)//for each neurone in the last layer
    {
        printf("%f\n", i->output);
        printf("_____________\n");       
    }
}

int main ()
{
    srand(time (NULL));
    int layer[2] = {2, 1};
    NeuralNetwork neuralnetwork = creat_neuralNetwork(2, layer, 2);
    XORtraining(1000000, neuralnetwork);
    printf("1 - 1 : ");
    XOR(neuralnetwork, 1.0, 1.0);
    printf("0 - 1 : ");
    XOR(neuralnetwork, 0.0, 1.0);
    printf("1 - 0 : ");
    XOR(neuralnetwork, 1.0, 0.0);
    printf("0 - 0 : ");
    XOR(neuralnetwork, 0.0, 0.0);
    free_neuralNetwork(neuralnetwork);
    return 0;
}