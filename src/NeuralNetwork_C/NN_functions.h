/*!
 *  File created on 12/10/2020 (MM/DD/YYYY) by florian.drevet
 *  Contributors : florian.drevet
 *
 *  Usefull functions to train a neuralnetwork
 * 
 */

#ifndef NN_FUNCTIONS_H_
#define NN_FUNCTIONS_H_
#include <math.h>
#include "neuralnetwork.h"

double sigmoid(double gitant);
void feedForward(NeuralNetwork neuralnetwork, double *inputs, int len);
double* print_output(NeuralNetwork neuralnetwork);
void backPropagation(NeuralNetwork neuralnetwork, double waited[]);
void updateWeigth(NeuralNetwork neuralnetwork, double *inputs, int len, double coeff);

#endif