/*!
 *  File created on 10/15/2020 (MM/DD/YYYY) by leo.duboin
 *  Contributors : leo.duboin
 *
 *  This file contains all the necessary to apply
 *  the text segmentation process to an image.
 */

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include "../Image/image.h"
#include "../NeuralNetwork_C/neuralnetwork.h"
#include "../NeuralNetwork_C/OCR_NN.h"
#include "../NeuralNetwork_C/NN_functions.h"
#include "../NeuralNetwork_C/DataManipulation.h"
#include "boundaryBox.h"

// segmentation.c ------------------


typedef enum HistogramType { LINE, COLUMN } HistogramType;

typedef struct Histogram {
    int *histo;
    HistogramType type;
    int threshold[2];
    int mean, size;
} Histogram;

void segmentation(Image *image);      // classic arrray implementation
void lineSegmentation(Image *image);
void bin_segmentation(Image *image, FILE *f);  // binaryTree implementation

#endif
