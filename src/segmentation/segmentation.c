#include "segmentation.h"

//---------------------------------------------

Histogram columnHistogram(Image *image);
Histogram lineHistogram(Image *image);
int *findBlocks(Histogram histo);

//---------------------------------------------

// Highlights what the algorithm thinks is a line
void segmentLine(Image *image) {
    Histogram histo = lineHistogram(image);
    int *histoH = histo.histo;
    int mean = 0;

    if (image->imageType != BW) {
        printf(
            "ERROR - segmentation.c : Image must have been binarized "
            "beforehand.\n");
        return;
    }

    for (int y = 0; y < image->height; y++) {
        if (histoH[y] > histo.mean) {
            for (int x = 0; x < image->width; x++)
                setPixelColor(image, BLACK, x, y);
        }
    }
}

#pragma region histogram

// @return the image's pixel histogram line per line
Histogram lineHistogram(Image *image) {
    int *histo = calloc(image->height, sizeof(int));
    int *ptr_histo = histo;
    int mean = 0;

    for (int y = 0; y < image->height; y++) {
        ptr_histo = &histo[y];
        for (int x = 0; x < image->width; x++)
            *ptr_histo += getPixelColor(image, x, y) == BLACK;
        mean += *ptr_histo;
    }

    Histogram res = {
        histo, LINE, {16, 16}, mean / (2 * image->height), image->height};
    return res;
}

// @return the image's pixel histogram column per column
Histogram columnHistogram(Image *image) {
    int *histo = calloc(image->width, sizeof(int));
    int *ptr_histo = histo;
    int mean = 0;

    for (int x = 0; x < image->width; x++) {
        ptr_histo = &histo[x];
        for (int y = 0; y < image->height; y++)
            *ptr_histo += getPixelColor(image, x, y) == BLACK;
        mean += *ptr_histo;
    }

    Histogram res = {
        histo, COLUMN, {16, 16}, mean / (2 * image->width), image->height};
    return res;
}

void displayHisto(Image *image) {
    int *histo = lineHistogram(image).histo;
    int a = 0;

    for (int y = 0; y < image->height; y++) {
        a = 0;
        for (int x = 0; x < image->width; x++) {
            a += getPixelColor(image, x, y) == BLACK;
            if (x <= histo[y])
                setPixelColor(image, BLACK, x, y);
            else
                setPixelColor(image, WHITE, x, y);
        }
    }

    displayImage(image);
    free(histo);
}

#pragma endregion histogram

/*!
 * @returns An array of the form [size, (start, end), ..., (start, end)]
 *      with each tuple representing the start and the end of a block.
 *      Size is used to give the resulting array's size.
 */
int *findBlocks(Histogram histo) {
    // TODO
}