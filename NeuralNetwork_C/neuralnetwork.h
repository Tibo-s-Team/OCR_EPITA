#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_
#define INPUT 2
#define HIDDEN_LAYER [2, 2]
#define OUTPUT_LAYER 1

typedef struct Neuronne Neuronne;
struct Neuronne
{
    int nbr_poids;
    double weigth;
    double biais;
    double error;
    double output;
};

Neuronne creat_neuronne(size_t nbr_poids);

#endif