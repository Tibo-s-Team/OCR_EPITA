#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "neuralnetwork.h"
#include "NN_functions.h"

int main(int argc, char *argv[]) {
    srand(time (NULL));
    int layer[3] = {3,5,8};
    double inputs[5] = {0.5,0.2,0.1,0.6,0.5};
    NeuralNetwork neuralnetwork = creat_neuralNetwork(5, layer, 3);
    feedForward(neuralnetwork, inputs, 5);
    free(print_output(neuralnetwork));
    free_neuralNetwork(neuralnetwork);
    return 0;
}
