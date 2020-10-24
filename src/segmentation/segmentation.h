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

// classic arrray implementation
void segmentation(Image *image);
int *segmentLine(Image *image);
// binaryTree implementation
void bin_segmentLine(Image *image);

// binaryTree.c

typedef struct BinTree {
    int key[2];
    struct BinTree *child;
    struct BinTree *sibling;
    struct BinTree *parent;
} BinTree;

BinTree createBinTree(int start, int end);
void addSibling(BinTree *new, BinTree *dest);
void addChild(BinTree *new, BinTree *dest);
void mapFunction(BinTree *tree, Image *image, void (*f)(Image *, BinTree *));
void printBranch(BinTree *node);

#endif
