/*!
 *  File created on 12/10/2020 (MM/DD/YYYY) by florian.drevet
 *  Contributors : florian.drevet
 *
 *  Usefull functions to train a neuralnetwork
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "neuralnetwork.h"
#include "NN_functions.h"
#include <math.h>

/*!
 * Activation function 
 * @param x the number to apply the sigmoid function
 * @return the value calculated
 */
double sigmoid(double x)
{
    return 1/(1 + exp(-x));
}

/*!
 * The derivated simgoid function
 * @param x the number to apply the sigmoid function
 * @return the value calculated
 */
double sigmoidPrime(double x)
{
    return x * (1-x);
}

/*!
 * The feedwork of a neural network
 * 
 * @param neuralnetwork the neuralnetwork to feedforward
 * @param inputs the inputs to give to our neuralnetwork
 * @param len the number of inputs
 */
void feedForward(NeuralNetwork neuralnetwork, double *inputs, int len)
{
    for(int i = 0; i < neuralnetwork.nbr_layers; i++) //for each layers
    {
        Layer *layer = neuralnetwork.layer +i;
        for(int j = 0; j < layer->nbr_neuronnes; j++) //for each neurones for each layers
        {
            Neuronne *neuronne = (layer->neuronne)+j;
            double somme = 0.0;
            int length;
            if (i == 0) //if it's the first layer 
            {
                length = len; //the number of before output values is the length of the inputs
            }
            else
            {
                length = (layer-1)->nbr_neuronnes;  //the number of before output values is the number 
                                                    //of neuronne in the layer before
            }
            for(int k = 0; k < length; k++) //for the number of output value before
            {
                double *weigth = neuronne->weigth;
                
                if(i == 0) //if it's the first layer the before output value is the input given in param
                {
                    somme += *(inputs + k) * (*(weigth + k)); //mltiply each input values by the weigth associated
                }
                else
                {
                    Neuronne *neuronne_precedent = (layer-1)->neuronne;
                    somme += (neuronne_precedent + k)->output * (*(weigth + k));
                    //multiply each output of neurones from the layer before by the weigth associated
                }
                      
            }
            neuronne->output = sigmoid(somme + neuronne->biais); 
            //set the output value of the neurone by the add of the summ and the biais of the neurone
            //we add to activat it by using the sigmoid function
        }
    }
}

/*!
 * Give a pointer to all the output of the last layer (the output layer)
 * This pointer will be use to know what is the answer of our neuralnetwork for a given inputs
 * In order to print in the console the values of the ouput of the last layer, uncomment the line in this function
 * 
 * @param neuralnetwork the neuralnetwork to print the output
 * @return the pointer to the ouput
 */
double* print_output(NeuralNetwork neuralnetwork)
{
    double* output = malloc((neuralnetwork.end -1)->nbr_neuronnes * sizeof(double));//lock memory for the pointer of output
    //(neuralnetwork.end -1)->nbr_neuronnes numbe of neurone in the last layer
    double* j = output;
    Layer *layer = neuralnetwork.end -1;
    for(Neuronne *i = layer->neuronne; i < layer->end; i++)//for each neurone in the last layer
    {
        printf("%f\n", i->output); //line to uncomment to print the ouput of each neuronne
        printf("_____________\n");
        *j = i->output;
        j++;
    }
    return output;
}

/*!
 * The backpropagation of a neural network
 * @param neuralnetwork the neuralnetwork to feedforward
 * @param inputs the inputs to give to our neuralnetwork
 * @param len the number of inputs
 */
void backPropagation(NeuralNetwork neuralnetwork, double waited[])
{
    for(int i = neuralnetwork.nbr_layers-1; i >= 0; i--)//for each layer in the neuralnetwork
    {
        Layer *layer = neuralnetwork.layer + i;
        if(i == neuralnetwork.nbr_layers-1) //if it's the last layer (the output layer)
        {
            for(int j = 0; j < layer->nbr_neuronnes; j++)//for each neuronne of the output layer
            {
                Neuronne *neuronne = layer->neuronne + j;
                neuronne->error = (waited[j] - neuronne->output) * sigmoidPrime(neuronne->output);
                //calculate the error coeff of each neuronne of the output layer
                //compare the value waited and the value we had
            }
        }
        else
        {
            Layer *next_layer = neuralnetwork.layer + i + 1; //the layer after the layer where we are
            for(int j = 0; j < layer->nbr_neuronnes; j++) //for each neurone in the layer where we are
            {
                double error = 0; //calculate the error
                for(int k = 0; k < next_layer->nbr_neuronnes; k++) //for each neuonne in the layer after
                {
                    Neuronne *neuronne = next_layer->neuronne+k;
                    error += *(neuronne->weigth + j) * neuronne->error;
                }
                Neuronne *neuronne = layer->neuronne + j;
                neuronne->error = error * sigmoidPrime(neuronne->output);
            }
        }
    }
}


/*!
 * Update the weight and the biais of ecah neuronne of the neuralnetwork with the error coef
 * @param neuralnetwork the neuralnetwork to feedforward
 * @param inputs the inputs to give to our neuralnetwork
 * @param len the number of inputs
 * @param coeff multiplication of each weigth
 */
void updateWeigth(NeuralNetwork neuralnetwork, double *inputs, int len, double coeff)
{
    for(int i = 0; i < neuralnetwork.nbr_layers; i++)
    {
        Layer *layer = neuralnetwork.layer + i;
        for(int k = 0; k < layer->nbr_neuronnes; k++)
        {
            Neuronne *neuronne = layer->neuronne + k;
            double* weigth = neuronne->weigth;
            if(i == 0)
            {
                for(int j = 0; j < len; j++)
                {
                    *(weigth + j) += coeff * neuronne->error * *(inputs + j); 
                }
            }
            else
            {
                Layer *before_layer = neuralnetwork.layer + i - 1;
                for(int j = 0; j < before_layer->nbr_neuronnes; j++)
                {
                    Neuronne *before_neuronne = before_layer->neuronne + j;
                    *(weigth + j) += coeff * neuronne->error * before_neuronne->output;
                }
            }
            neuronne->biais += coeff * neuronne->error;
        }
    }
}