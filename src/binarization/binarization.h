#ifndef BINARIZATION
#define BINARIZATION

#include "../image.h"

// Bradley.c

void Bradley(char *filename, char *output);



//Otsu.c

void Otsu(char *filename, char *output);

void histogramGray(Image img, unsigned long histogram[]);

unsigned long Threshold(unsigned long histogram[]);


#endif
