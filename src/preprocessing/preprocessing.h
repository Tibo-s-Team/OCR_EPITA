/*!
 *  File created on 10/12/2020 (MM/DD/YYYY) by leo.duboin
 *  Contributors : leo.duboin
 *
 *  File containing the functions necessary to the image preprocessing process.
 *  This process is used to have the best image quality possible so that
 *  the image segmentation and more particularily the neural network analysis
 *  work even better.
 */

#ifndef PREPROCESSING_H_
#define PREPROCESSING_H_

#include "../image.h"

// suppression_couleurs.c ----

void grayscale(Image *image);
void grayscaleTest(Image *image);
void blackAndWhite(Image *image);

// filtrage.c ----------------

typedef unsigned char Uint8;

typedef struct Kernel {
    int *matrix;
    int size;  // kernel : size * size
} Kernel;

typedef enum filter_type {
    COUNTOURS,
    MEDIAN,
    GAUSSIAN  // Doesn't work
} Filter;

void filterImage(Image *image, Filter filter);

#endif
