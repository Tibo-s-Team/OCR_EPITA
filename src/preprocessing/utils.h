#ifndef UTILS_H_
#define UTILS_H_

#include "preprocessing.h"

#define PI 3.14159265358

// convolution filters
Kernel averageFilter();
Kernel gaussianFilter();
Kernel contoursFilter();
Kernel sharpnessFilter();
Kernel edgeFilter();
Kernel sobelFilter();

// median
Uint8 medianFilter(Image *image, int size, int x, int y);

// utils
void swap(int *a, int *b);
void printKernel(Kernel kernel);
void sortList(int *list, int size);
void printList(int *list, int size);
void reverseColor(Image *image);

#endif