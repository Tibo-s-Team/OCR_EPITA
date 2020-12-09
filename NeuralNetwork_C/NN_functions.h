#ifndef NN_FUNCTIONS_H_
#define NN_FUNCTIONS_H_
#include <math.h>
#include "neuralnetwork.h"

double sigmoid(double gitant);
void feedForward(NeuralNetwork neuralnetwork, double inputs[], int len);
double* print_output(NeuralNetwork neuralnetwork);

#endif