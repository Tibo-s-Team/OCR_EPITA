#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include "../image.h"

// segmentation.c

typedef enum HistogramType { LINE, COLUMN } HistogramType;

typedef struct Histogram {
    int *histo;
    HistogramType type;
    int threshold[2];
    int mean, size;
} Histogram;

void segmentLine(Image *image);
void displayHisto(Image *image);

// binaryTree.c

typedef struct BinTree {
  int key[2];
  struct BinTree *child;
  struct BinTree *sibling;
} BinTree;

BinTree createBinTree(int start, int end);
void appendBinTree(BinTree *new, BinTree *dest);

#endif
