#include <stdio.h>
#include <stdlib.h>
#include "XOR.h"
#include <math.h>

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
    free(print_output(neuralnetwork));
}