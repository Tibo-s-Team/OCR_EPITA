/*!
 *  File created on 10/12/2020 (MM/DD/YYYY) by leo.duboin
 *  Contributors : leo.duboin
 *
 *  File containing the necessary functions to apply filters onto an image.
 *
 *  12/13/2020 : added gaussian filter (bugged) + fixed convolution
 *  12/14/2020 : added median filtering + external funtion call handler
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "preprocessing.h"
#define PI 3.14159265358

//--------------------------------
// median
void medianFiltering(Image *image);
// convolution
void convolution(Image *image, Kernel (*f)());
void convolutePixel(Image *image, Kernel kernel, int x, int y);
void reverseKernel(Kernel kernel);
// utils
void swap(int *a, int *b);
void printKernel(Kernel kernel);
void sortList(int *list, int size);
void printList(int *list, int size);
// filters
Kernel gaussianFilter();
Kernel contoursFilter();
Kernel sharpnessFilter();
Uint8 medianFilter(Image *image, int size, int x, int y);
//--------------------------------

/*!
 * Main funtion to call outside the file.
 * Apply a filter onto an image.
 * @param image the image to apply the filter onto
 * @param filter the type of filter to apply
 */
void filterImage(Image *image, Filter filter) {
    switch (filter) {
        case CONTOURS:
            convolution(image, contoursFilter);
            break;
        case SHARPNESS:
            convolution(image, sharpnessFilter);
            break;
        case GAUSSIAN:
            convolution(image, gaussianFilter);
            break;
        case MEDIAN:
            medianFiltering(image);
            break;
        default:
            errx(1, "Error: filtrage.c: filterImage: invalid filter type.");
            break;
    }
}

#pragma region filtering

void convolution(Image *image, Kernel (*f)()) {
    Kernel kernel = (*f)();
    reverseKernel(kernel);
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

    for (int i = 0; i < kernel.size; ++i) {
        for (int j = 0; j < kernel.size; ++j) {
            // multiplier les elements correpondants (k[i,j] *
            // pixels[x-1+i,y-1+j]) additioner tous les resultats des
            // multiplications
            int I = i - center, J = j - center;
            int value = kernel.matrix[(kernel.size * i) + j];
            Uint8 color = getPixelColor(image, x + J, y + I);
            // printf("%d * %d\n", value, color);

            pixel += value * color;
        }
    }

    pixel /= kernel.size * kernel.size;
    setPixelColor(image, (Uint8)pixel, x, y);
}

/*!
 * Reverse the columns and the lines of a kernel (matrix).
 * [ [0,1],[2,3] ] => [ [3,2],[1,0] ]
 * @param kernel the kernel whose columns/lines we want to inverse
 */
void reverseKernel(Kernel kernel) {
    int total_size = kernel.size * kernel.size;
    for (int i = 0; i < total_size / 2;
         ++i) {  // swap doesn't work here idk why
        int a = kernel.matrix[i], b = kernel.matrix[total_size - i - 1];
        kernel.matrix[i] = b;
        kernel.matrix[total_size - i - 1] = a;
    }
}

/*!
 * Apply median filtering onto an image.
 */
void medianFiltering(Image *image) {
    if (image->imageType == RGB)
        errx(1,
             "Error: filtrage.c: medianFiltering: "
             "given image is of RGB type.");

    int size = 3;
    int center = size / 2;

    for (int y = center; y < image->height - center; ++y) {
        for (int x = center; x < image->width - center; ++x) {
            Uint8 color = medianFilter(image, size, x, y);
            setPixelColor(image, color, x, y);
        }
    }
}

#pragma endregion filtering

#pragma region filter

/*!
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

Kernel sharpnessFilter() {
    int *k = (int *)calloc(3 * 3, sizeof(int));

    // corners = 0
    k[0] = 0;
    k[2] = 0;
    k[6] = 0;
    k[8] = 0;
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
 * @return the pixel value according to the median filtering algorithm
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
 * Prints the content of a list
 */
void printList(int *list, int size) {
    printf("[");
    for (int i = 0; i < size; ++i) printf("%d; ", list[i]);
    printf("]\n");
}

#pragma endregion utils