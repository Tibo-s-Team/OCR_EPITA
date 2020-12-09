#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "neuralnetwork.h"
#include "NN_functions.h"
#include "XOR.h"

int main(int argc, char *argv[]) {
    srand(time (NULL));
    int layer[2] = {2, 1};
    NeuralNetwork neuralnetwork = creat_neuralNetwork(2, layer, 2);
    XORtraining(100000, neuralnetwork);
    XOR(neuralnetwork, 1.0, 1.0);
    free_neuralNetwork(neuralnetwork);
    return 0;
}
