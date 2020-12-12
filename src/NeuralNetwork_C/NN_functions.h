#ifndef NN_FUNCTIONS_H_
#define NN_FUNCTIONS_H_
#include <math.h>
#include "neuralnetwork.h"

double sigmoid(double gitant);
void feedForward(NeuralNetwork neuralnetwork, double *inputs, int len);
double* print_output(NeuralNetwork neuralnetwork);
void backPropagation(NeuralNetwork neuralnetwork, double waited[]);
void print_error(NeuralNetwork neuralnetwork);
void updateWeigth(NeuralNetwork neuralnetwork, double *inputs, int len, double coeff);

#endif