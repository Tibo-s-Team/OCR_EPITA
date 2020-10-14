#include <stdio.h>
#include <stdlib.h>

#include "../image.h"

//---------------------------------------------

Uint8 *verticalHistogram(Image *image);
Uint8 *horizontalHistogram(Image *image);

//---------------------------------------------

void segmentLine(Image *image) {
    Uint8 *histo = horizontalHistogram(image);
    int mean = 0;

    if (image->imageType != BW) {
        printf(
            "ERROR - segmentation.c : Image must have been binarized "
            "beforehand.\n");
            return;
    }

    for (int y = 0; y < image->height; y++) mean += histo[y];
    mean /= 2 * image->height;

    for(int y = 0; y < image->height; y++){
        if(histo[y] > mean){
            for(int x = 0; x < image->width; x++)
                setPixel(image, 0, x, y);
        }
    }
}

Uint8 *horizontalHistogram(Image *image) {
    Uint8 *res = malloc(image->height * sizeof(Uint8));
    Uint8 *ptr_res = res;

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