/*!
 *  File created on 10/12/2020 (MM/DD/YYYY) by leo.duboin
 *  Contributors : leo.duboin
 *
 *  File containing the necessary functions to apply filters onto an image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "preprocessing.h"

//--------------------------------

void reverseKernel(Kernel *kernel);
void swap(Uint8 *a, Uint8 *b);

//--------------------------------

void convolution(Kernel *kernel) {
    // TODO
    // reverse columns and lines of k - Done
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
/*!
 * Reverse the columns and the lines of a kernel (matrix).
 * [ [0,1],[2,3] ] => [ [3,2],[1,0] ]
 * @param kernel the kernel whose columns/lines we want to inverse
 */
void reverseKernel(Kernel *kernel) {
    int width = kernel->width, height = kernel->height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // column inversion
            if (x < width / 2) {
                swap(&kernel->matrix[y * width + x],
                     &kernel->matrix[(y + 1) * width - x - 1]);
            }
            // line inversion
            if (y >= height / 2) {
                int symetric_y = height - 1 - y;
                swap(&kernel->matrix[y * width + x],
                     &kernel->matrix[symetric_y * width + x]);
            }
        }
    }
}

/*!
 * swaps the values of 2 unsigned char
 * @param a unsigned char pointer
 * @param b unsigned char pointer
 */
void swap(Uint8 *a, Uint8 *b) {
    int tmp = *a;

    *a = *b;
    *b = tmp;
}

/*!
 * Displays the content of the kernel's matrix in a table like format.
 * @param kernel the kernel to print
 */
void printKernel(Kernel *kernel) {
    Uint8 *matrix = kernel->matrix;
    int length = 0;

    while (length < kernel->width * kernel->height) {
        printf("|%d", *matrix++);
        if (++length % kernel->width == 0) printf("|\n-------\n");
    }

    printf("\n======\n\n");
}