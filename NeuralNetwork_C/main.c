#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "neuralnetwork.h"

int main(int argc, char *argv[]) {
    int layer[3] = {2,2,2};
    NeuralNetwork neuralnetwork = creat_neuralNetwork(3, layer, 3);
    free_neuralNetwork(neuralnetwork);
    return 0;
}
