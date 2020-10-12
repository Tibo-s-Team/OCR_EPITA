#include "filtrage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------

void reverseKernel(Kernel *kernel);
void swap(Uint8 *a, Uint8 *b);

//--------------------------------

void convolution(Kernel *kernel) {
    // reverse columns and lines of k
    // place chosen pixel in the center of the kernel
    // multiplier les elements correpondants (k[i,j] * pixels[x-1+i, y-1+j])
    // additioner tous les resultats des multiplications

    Kernel tmp = *kernel;
    Kernel *k = &tmp;
    // Copy the given kernel
    tmp.matrix = malloc(tmp.width * tmp.height * sizeof(Uint8));
    memcpy(tmp.matrix, kernel->matrix, tmp.width * tmp.height * sizeof(Uint8));
}

// reverse columns and lines of k
void reverseKernel(Kernel *kernel) {
    // reverse columns and lines of k
    int width = kernel->width, height = kernel->height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // inversion colonnes
            if (x < width / 2) {
                swap(&kernel->matrix[y * width + x],
                     &kernel->matrix[(y + 1) * width - x - 1]);
            }
            // inversion lignes
            if (y >= height / 2) {
                int symetric_y = height - 1 - y;
                swap(&kernel->matrix[y * width + x],
                     &kernel->matrix[symetric_y * width + x]);
            }
        }
    }
}

// swaps the values of 2 unsigned char
void swap(Uint8 *a, Uint8 *b) {
    int tmp = *a;

    *a = *b;
    *b = tmp;
}

// Displays the content of the kernel's matrix in a table like format.
void printKernel(Kernel *kernel) {
    Uint8 *matrix = kernel->matrix;
    int length = 0;

    while (length < kernel->width * kernel->height) {
        printf("|%d", *matrix++);
        if (++length % kernel->width == 0) printf("|\n-------\n");
    }

    printf("\n======\n\n");
}