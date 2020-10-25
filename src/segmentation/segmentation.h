/*!
 *  File created on 10/15/2020 (MM/DD/YYYY) by leo.duboin
 *  Contributors : leo.duboin
 *
 *  This file contains all the necessary to apply 
 *  the text segmentation process to an image.
 */

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include "../image.h"
#include "binaryTree.h"

// segmentation.c ------------------

typedef enum HistogramType { LINE, COLUMN } HistogramType;

typedef struct Histogram {
    int *histo;
    HistogramType type;
    int threshold[2];
    int mean, size;
} Histogram;

void segmentation(Image *image);      // classic arrray implementation
void bin_segmentation(Image *image);  // binaryTree implementation

#endif
