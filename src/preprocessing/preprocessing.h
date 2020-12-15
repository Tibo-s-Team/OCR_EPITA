/*!
 *  File created on 10/12/2020 (MM/DD/YYYY) by leo.duboin
 *  Contributors : leo.duboin
 *
 *  File containing the functions necessary to the image preprocessing process.
 *  This process is used to have the best image quality possible so that
 *  the image segmentation and more particularily the neural network analysis
 *  work even better.
 *
 *  12/14/2020 : added filter_type enum to simplify external function call
 */

#ifndef PREPROCESSING_H_
#define PREPROCESSING_H_

#include "../binarization/binarization.h"
#include "../Image/image.h"

// suppression_couleurs.c ----

void grayscale(Image *image);
void blackAndWhite(Image *image);

// filtrage.c ----------------

typedef unsigned char Uint8;

/*!
 * Basic structure of a kernel used for convolution.
 * @param matrix the kernel itself
 * @param size the size of the kernel (size * size)
*/
typedef struct Kernel {
    int *matrix;
    int size;  // kernel : size * size
} Kernel;

/*!
 * List of all the different filter types
*/
typedef enum filter_type {
    SHARPNESS,  // Really Useful
    AVERAGE,    // Useful
    MEDIAN,     // Meh
    CONTOURS,   // Test
    EDGE,       // Test
    SOBEL,      // Test
    GAUSSIAN    // Doesn't work
} Filter;

void filterImage(Image *image, Filter filter);

#endif
