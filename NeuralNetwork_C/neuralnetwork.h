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

Neuronne creat_neuronne(size_t nbr_poids);
Layer creat_layer(int nbr_poids, int nbr_neuronne);
void free_layer(Layer layer);

#endif