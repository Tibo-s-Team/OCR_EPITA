/*!
 *  File created on 12/9/2020 (MM/DD/YYYY) by florian.drevet
 *  Contributors : florian.drevet
 *
 *  The structure of a neural network
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "neuralnetwork.h"

/*!
 * creat a random double between min and max exclued
 * @param min the min value of the random
 * @param max the max value of the random
 * @return a random number
 */
double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    double res = min + (rand() / div);
    if (res == 1 || res == -1)
        return randfrom(min, max);
    else
        return res;
}


/*!
 * Creat a new neuronne
 * .weigth has values between -1 and 1 exclued
 * .biais has a value between -1 and 1 exclued
 * @param nbr_poids
 * @return a new neuronne
 */
Neuronne creat_neuronne(size_t nbr_poids)
{
    double *begin_weigth = malloc(nbr_poids * sizeof(double));
    double *end_weight = begin_weigth + nbr_poids;
    for(double *i = begin_weigth; i < end_weight; i++)
    {
       *i = randfrom(-1.0, 1.0); 
    }
    double biais = randfrom(-1.0, 1.0);
    struct Neuronne neuronne = {nbr_poids, begin_weigth, end_weight, biais, 0.0, 0.0};
    int j = 0;
    for(double *i = begin_weigth; i < end_weight; i++)
    {
        j++;
    }
    return neuronne;
}

/*!
 * Creat a layer. 
 * @param nbr_poid the number of neuronnes in the layer before
 * @param nbr_neuronnes number of neuronne of this layer
 * @return a new layer
 */
Layer creat_layer(int nbr_poids, int nbr_neuronnes)
{
    Neuronne *begin_layer = malloc(nbr_neuronnes * sizeof(Neuronne));
    Neuronne *end_layer = begin_layer + nbr_neuronnes;
    for(Neuronne *i = begin_layer; i < end_layer; i++)
    {
        Neuronne neuronne = creat_neuronne(nbr_poids);
        *i = neuronne; 
    } 
    Layer layer = {nbr_neuronnes, begin_layer, end_layer};
    return layer;
}

/*!
 * free the memory allocated to a layer
 * @param layer the layer to free
 */
void free_layer(Layer layer)
{
    for(Neuronne *i = layer.neuronne; i < layer.end; i++)
    {
        free(i->weigth);
    }
    free(layer.neuronne);
}

/*!
 * creat a neuralnetwork
 * @param nbr_inputs number of inputs of our neuralnetwork
 * @param layers an array that represent the layer
 * the number of element is the number of layers
 * each element is the number of neuronne of the layer
 * @param len the length of the layer array
 * @return a new neuralnetwork
 */
NeuralNetwork creat_neuralNetwork(int nbr_inputs, int layers[], int len)
{

    Layer *begin_neuralnetwork = malloc(len * sizeof(Layer));
    Layer *end_neuralnetwork = begin_neuralnetwork + len;
    int j = 0;
    for(Layer *i = begin_neuralnetwork; i < end_neuralnetwork ; i++)
    {
        if (j == 0)
        {
            Layer layer = creat_layer(nbr_inputs, layers[0]);
            *i = layer;
        }
        else
        {
            Layer layer = creat_layer((i-1)->nbr_neuronnes, layers[j]);
            *i = layer;
        }
        j += 1;
    }
    NeuralNetwork neuralnetwork = {j, nbr_inputs, begin_neuralnetwork, end_neuralnetwork};
    return neuralnetwork;
}

/*!
 * free the memory allocated to a neuralnetwork
 * @param neurlnetwork the neuralnetwork to free
 */
void free_neuralNetwork(NeuralNetwork neuralnetwork)
{
    for(Layer *i = neuralnetwork.layer; i < neuralnetwork.end; i++)
    {
        free_layer(*i);
    }
    free(neuralnetwork.layer);
}


