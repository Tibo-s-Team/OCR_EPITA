/*!
 *  File created on 12/9/2020 (MM/DD/YYYY) by florian.drevet
 *  Contributors : florian.drevet
 *
 *  The structure of a neural network
 * 
 */

#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

typedef struct Neuronne
{
    int nbr_poids;
    double *weigth;
    double *end;
    double biais;
    double error;
    double output;
}Neuronne;

typedef struct Layer
{
    int nbr_neuronnes;
    Neuronne *neuronne;
    Neuronne *end;
}Layer;

typedef struct NeuralNetwork 
{
    int nbr_layers;
    int nbr_inputs; 
    Layer *layer;
    Layer *end;
}NeuralNetwork;

Neuronne creat_neuronne(size_t nbr_poids);
Layer creat_layer(int nbr_poids, int nbr_neuronne);
void free_layer(Layer layer);
NeuralNetwork creat_neuralNetwork(int nbr_inputs, int layers[], int len);
void free_neuralNetwork(NeuralNetwork neuralnetwork);

#endif