/*
 * File created by Léo DUBOIN on 12/14/2020.
 */

#include "utils.h"

#pragma region filters

/*!
 * @warning Doesn't work
 * @return an istance of a gaussian filter
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
    printKernel(res);
    return res;
}

/*!
 * Used as a test for the convolution algorithm
 * @return a kernel for contour filtering.
 */
Kernel contoursFilter() {
    int *k = (int *)calloc(3 * 3, sizeof(int));
    for (int i = 0; i < 9; i++) k[i] = -1;
    k[4] = 8;
    Kernel res = (Kernel){k, 3};
    printKernel(res);
    return res;
}

/*!
 * Used as a test for the convolution algorithm
 * @return a kernel for edge filtering.
 */
Kernel edgeFilter() {
    int *k = (int *)calloc(3 * 3, sizeof(int));
    k[3] = -1;
    k[4] = 1;
    Kernel res = (Kernel){k, 3};
    printKernel(res);
    return res;
}

/*!
 * @return a kernel for accentuating contours.
 */
Kernel sharpnessFilter() {
    int *k = (int *)calloc(3 * 3, sizeof(int));

    // cross = -1
    k[1] = -1;
    k[3] = -1;
    k[5] = -1;
    k[7] = -1;
    // center = 5
    k[4] = 5;

    Kernel res = (Kernel){k, 3};
    printKernel(res);
    return res;
}

/*!
 * Used as a test for the convolution algorithm
 * @return sobel's kernel.
 */
Kernel sobelFilter() {
    int *k = (int *)calloc(3 * 3, sizeof(int));

    k[0] = -1;
    k[2] = 1;
    k[3] = -2;
    k[5] = 2;
    k[6] = -1;

    Kernel res = (Kernel){k, 3};
    printKernel(res);
    return res;
}

/*!
 * @return a kernel for filtering through average value.
 */
Kernel averageFilter() {
    int *k = (int *)calloc(3 * 3, sizeof(int));
    for (int i = 0; i < 9; ++i) k[i] = 1;

    Kernel res = (Kernel){k, 3};
    printKernel(res);
    return res;
}

/*!
 * @return the pixel value according to the median filtering algorithm
 * @param image the image containing the pixel
 * @param size the size of the resulting kernel (size * size)
 * @param x pixel's x coordinate
 * @param y pixel's y coordinate
 */
Uint8 medianFilter(Image *image, int size, int x, int y) {
    int center = size / 2;

    if (x < center || y < center)
        errx(1,
             "Error: filtrage.c : convolutePixel - "
             "Pixel coordinate doesn't fit, (%d,%d) with a kernel of size %d",
             x, y, size);
    if (x > image->width - center || y > image->height - center)
        errx(1,
             "Error: filtrage.c : convolutePixel - "
             "Pixel coordinate doesn't fit, (%d,%d) with a kernel of size %d "
             "and image of size %dx%d",
             x, y, size, image->width, image->height);

    int *values = (int *)calloc(size * size, sizeof(int));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; ++j) {
            Uint8 color = getPixelColor(image, x + i - center, y + j - center);
            values[i * size + j] = color;
        }
    }

    sortList(values, size * size);
    Uint8 res = (Uint8)values[(size * size) / 2];
    free(values);
    return res;
}

#pragma endregion filters

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
void printKernel(Kernel kernel) {
    int *matrix = kernel.matrix;
    int length = 0;

    while (length < kernel.size * kernel.size) {
        printf("|%d", *matrix++);
        if (++length % kernel.size == 0) printf("|\n-------\n");
    }

    printf("\n======\n\n");
}

/*!
 * Sorts a list using simple bubble sort
 * @param list a list of int
 * @param size the size of the list
 */
void sortList(int *list, int size) {
    int sorted = 0;  // false
    int end = size;

    while (!sorted) {
        sorted = 1;  // true
        for (int i = 1; i < end; ++i) {
            if (list[i - 1] > list[i]) {
                swap(&list[i - 1], &list[i]);
                sorted = 0;  // false
            }
        }
        end--;
    }
}

/*!
 * Print the content of a list
 * @param list the list to print
 * @param size the total size of the list
 */
void printList(int *list, int size) {
    printf("[");
    for (int i = 0; i < size; ++i) printf("%d; ", list[i]);
    printf("]\n");
}

/*!
 * Reverse an image's colors
*/
void reverseColor(Image *image) {
    for (int y = 0; y < image->height; ++y) {
        for (int x = 0; x < image->width; ++x) {
            Uint8 color = 255 - getPixelColor(image, x, y);
            setPixelColor(image, color, x, y);
        }
    }
}

#pragma endregion utils
