#include <stdio.h>
#include <stdlib.h>
#include "neuralnetwork.h"


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

Neuronne creat_neuronne(size_t nbr_poids)
{
    double *begin_weigth = malloc(nbr_poids * sizeof(double));
    double *end_weight = begin_weigth + nbr_poids;
    for(double *i = begin_weigth; i < end_weight; i++)
    {
       *i = randfrom(-1.0, 1.0); 
    }
    double biais = randfrom(-1.0, 1.0);
    struct Neuronne neuronne = {nbr_poids, *begin_weigth, biais, 0, 0};
    return neuronne;
}




