#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "neuralnetwork.h"
#include "NN_functions.h"

int main(int argc, char *argv[]) {
    int layer[3] = {2,2,2};
    NeuralNetwork neuralnetwork = creat_neuralNetwork(3, layer, 3);
    feedForward(neuralnetwork, layer, 3);
    free_neuralNetwork(neuralnetwork);
    return 0;
}
