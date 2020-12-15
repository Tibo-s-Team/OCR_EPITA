#ifndef OCR_NN_H
#define OCR_NN_H

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include "neuralnetwork.h"
#include "NN_functions.h"
#include "../image.h"
#include <math.h>
#define NBR_LETTER 52
#define DONE 52

typedef struct Letter
{
    const char* path;
    int nbr_images;
    Image *img;
    char chara;
}Letter;

char output_to_char(struct NeuralNetwork neuralnetwork);
void one_training(NeuralNetwork neuralnetwork, 
                    double *inputs, 
                    int len_inputs, 
                    double waited_outputs[],
                    double coeff);
double *inputs (Image* img);
Letter creat_letter(char* path);
void training_NN(NeuralNetwork neuralnetwork, Letter tab_letter[NBR_LETTER], int len, double waited[NBR_LETTER][NBR_LETTER], int times, double coeff);
char print_res(NeuralNetwork neuralnetwork ,char* path);
Image resize_images(Image img);

#endif