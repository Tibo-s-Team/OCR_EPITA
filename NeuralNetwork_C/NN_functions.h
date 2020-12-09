#ifndef NN_FUNCTIONS_H_
#define NN_FUNCTIONS_H_
#include <math.h>
#include "neuralnetwork.h"

double sigmoid(double gitant);
void feedForward(NeuralNetwork neuralnetwork, int inputs[], int len);

#endif