#ifndef DATAMANIPULATION_H_
#define DATAMANIPULATION_H_

#include "neuralnetwork.h"

// Save neural network in the output file
void save(struct NeuralNetwork network, char *output);

// Loads neural network from the filename to the empty specified network
struct NeuralNetwork load(char *filename);

#endif


