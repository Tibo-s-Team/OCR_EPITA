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
#define PI 3.14159265358

//--------------------------------

void convolutePixel(Image *image, Kernel kernel, int x, int y);
void reverseKernel(Kernel *kernel);
void swap(int *a, int *b);
Kernel gaussianFilter();
Kernel detectContours();

//--------------------------------

#pragma region convolution

void convolution(Image *image) {
    // TODO
    // reverse columns and lines of k - Done

    Kernel kernel = detectContours();
    printKernel(&kernel);
    reverseKernel(&kernel);
    int center = kernel.size / 2;

    for (int y = center; y < image->height - center; ++y) {
        for (int x = center; x < image->width - center; ++x) {
            convolutePixel(image, kernel, x, y);
        }
    }
}

/*!
 * Apply convolution to a given pixel
 * @param image the image we want to apply convolution to
 * @param kernel the kernel we use for the convolution (already reversed !)
 */
void convolutePixel(Image *image, Kernel kernel, int x, int y) {
    // place chosen pixel in the center of the kernel
    int center = kernel.size / 2;
    if (x < center || y < center)
        errx(1,
             "Error: filtrage.c : convolutePixel - "
             "Pixel coordinate doesn't fit, (%d,%d) with a kernel of size %d",
             x, y, kernel.size);
    if (x > image->width - center || y > image->height - center)
        errx(1,
             "Error: filtrage.c : convolutePixel - "
             "Pixel coordinate doesn't fit, (%d,%d) with a kernel of size %d "
             "and image of size %dx%d",
             x, y, kernel.size, image->width, image->height);

    int pixel = 0;

    for (int i = -center; i < kernel.size - center; ++i) {
        for (int j = -center; j < kernel.size - center; ++j) {
            // multiplier les elements correpondants (k[i,j] * pixels[x-1+i,y-1+j]) 
            // additioner tous les resultats des multiplications
            pixel += kernel.matrix[kernel.size * i + j] *
                     getPixelColor(image, x + i, y + j);
        }
    }

    pixel /= kernel.size * kernel.size;
    setPixelColor(image, (Uint8)pixel, x, y);
}

// reverse columns and lines of k
/*!
 * Reverse the columns and the lines of a kernel (matrix).
 * [ [0,1],[2,3] ] => [ [3,2],[1,0] ]
 * @param kernel the kernel whose columns/lines we want to inverse
 */
void reverseKernel(Kernel *kernel) {
    int total_size = kernel->size * kernel->size;
    for (int i = 0; i < total_size / 2; ++i) {
        swap(&kernel->matrix[i], &kernel->matrix[total_size - i]);
    }
}

#pragma endregion convolution

#pragma region filter

/*!
 * Return an istance of a gaussian filter
 */
Kernel gaussianFilter() {
    // intialising standard deviation to 1.0
    double sigma = 1.0;
    double r, s = 2.0 * sigma * sigma;

    int *kernel = (int *)calloc(5 * 5, sizeof(int));

    // sum is for normalization
    double sum = 0.0;

    // generating 5x5 kernel
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            r = sqrt(x * x + y * y);
            kernel[(x + 2) * 5 + y * 2] = (exp(-(r * r) / s)) / (PI * s);
            sum += kernel[(x + 2) * 5 + y * 2];
        }
    }

    // normalising the Kernel
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j) kernel[(i * 5) + j] /= sum;

    Kernel res = {kernel, 5};
    printKernel(&res);
    return res;
}

Kernel detectContours() {
    int *k = (int *)calloc(3 * 3, sizeof(int));
    for (int i = 0; i < 9; i++) k[i] = -1;
    k[4] = 8;
    return (Kernel){k, 3};
}

#pragma endregion filter

#pragma region utils

/*!
 * swaps the values of 2 unsigned char
 * @param a unsigned char pointer
 * @param b unsigned char pointer
 */
void swap(int *a, int *b) {
    int tmp = *a;

    *a = *b;
    *b = tmp;
}

/*!
 * Displays the content of the kernel's matrix in a table like format.
 * @param kernel the kernel to print
 */
void printKernel(Kernel *kernel) {
    int *matrix = kernel->matrix;
    int length = 0;

    while (length < kernel->size * kernel->size) {
        printf("|%d", *matrix++);
        if (++length % kernel->size == 0) printf("|\n-------\n");
    }

    printf("\n======\n\n");
}

#pragma endregion utils
