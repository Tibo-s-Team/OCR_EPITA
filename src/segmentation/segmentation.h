#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include "../image.h"

typedef enum HistogramType { LINE, COLUMN } HistogramType;

typedef struct Histogram {
    int *histo;
    HistogramType type;
    int threshold[2];
    int mean, size;
} Histogram;

void segmentLine(Image *image);
void displayHisto(Image *image);

#endif
