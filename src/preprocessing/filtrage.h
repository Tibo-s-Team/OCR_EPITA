#ifndef PREPROCESSING_H_
#define PREPROCESSING_H_

typedef unsigned char Uint8;

typedef struct Kernel {
    Uint8 *matrix;
    int width, height;
} Kernel;

void convolution(Kernel *kernel);
void printKernel(Kernel *kernel);

#endif