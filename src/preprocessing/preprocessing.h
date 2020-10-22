#ifndef PREPROCESSING_H_
#define PREPROCESSING_H_

#include "../image.h"

// suppression_couleurs.c
void grayscale(Image *image);
void grayscaleTest(Image *image);
void blackAndWhite(Image *image);

// filtrage.c
typedef unsigned char Uint8;

typedef struct Kernel {
    Uint8 *matrix;
    int width, height;
} Kernel;

void convolution(Kernel *kernel);
void printKernel(Kernel *kernel);

#endif
