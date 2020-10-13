#include <stdio.h>
#include <stdlib.h>

#include "../image.h"

void printHisto(Uint8 *histo, int length);

Uint8 *horizontalHistogram(Image *image) {
    Uint8 *res = malloc(image->height * sizeof(Uint8));
    Uint8 *ptr_res = res;

    if (image->imageType != BW) {
        printf(
            "ERROR - segmentation.c : Image must have been binarized "
            "beforehand.\n");
        return res;
    }

    for (int y = 0; y < image->height; y++) {
        ptr_res = &res[y];
        for (int x = 0; x < image->width; x++)
            *ptr_res += getPixel(image, x, y) / 255;
    }

    return res;
}

Uint8 *verticalHistogram(Image *image) {
    Uint8 *res = malloc(image->width * sizeof(Uint8));
    Uint8 *ptr_res = res;

    if (image->imageType != BW) {
        printf(
            "ERROR - segmentation.c : Image must have been binarized "
            "beforehand.\n");
        return res;
    }

    for (int x = 0; x < image->width; x++) {
        ptr_res = &res[x];
        for (int y = 0; y < image->height; y++)
            *ptr_res += getPixel(image, x, y) / 255;
    }

    return res;
}