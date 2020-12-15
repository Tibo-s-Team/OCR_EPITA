/*
 * File created by Léo DUBOIN on 12/11/2020.
 * 
 * Simple implementation of a BoundaryBox structure.
 * Used to identify an area inside an image.
*/

#ifndef BOUNDARY_BOX_H_
#define BOUNDARY_BOX_H_

#include <stdio.h>

typedef struct PixelLocation {
    int x;
    int y;
} Pixel;

typedef struct BoundaryBox {
    Pixel start;    // Top left corner
    Pixel end;      // Bottom right corner
} BBox;

void printBox(BBox box);

#endif