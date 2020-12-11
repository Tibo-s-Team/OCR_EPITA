/*!
 *  File created on 10/15/2020 (MM/DD/YYYY) by leo.duboin
 *  Contributors : leo.duboin
 *
<<<<<<< HEAD
 *  This file contains all the necessary to apply 
=======
 *  This file contains all the necessary to apply
>>>>>>> 325a2fb694d9b09862640edd0a193487f93c7b60
 *  the text segmentation process to an image.
 */

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include "../image.h"
<<<<<<< HEAD
#include "binaryTree.h"

// segmentation.c ------------------

=======
#include "boundaryBox.h"

// segmentation.c ------------------


>>>>>>> 325a2fb694d9b09862640edd0a193487f93c7b60
typedef enum HistogramType { LINE, COLUMN } HistogramType;

typedef struct Histogram {
    int *histo;
    HistogramType type;
    int threshold[2];
    int mean, size;
} Histogram;

void segmentation(Image *image);      // classic arrray implementation
<<<<<<< HEAD
void lineSegmentation(Image *image);
=======
>>>>>>> 325a2fb694d9b09862640edd0a193487f93c7b60
void bin_segmentation(Image *image);  // binaryTree implementation

#endif
