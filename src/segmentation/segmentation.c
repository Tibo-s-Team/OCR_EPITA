#include "segmentation.h"

//---------------------------------------------

Uint8 *verticalHistogram(Image *image);
Uint8 *horizontalHistogram(Image *image);

//---------------------------------------------

// Highlights what the algorithm thinks is a line
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

    mean = (mean / image->height);

    for (int y = 0; y < image->height; y++) {
        if (histo[y] > mean) {
            for (int x = 0; x < image->width; x++)
                setPixelColor(image, BLACK, x, y);
        }
    }
}

#pragma region histogram

// @return the image's pixel histogram line per line
Uint8 *horizontalHistogram(Image *image) {
    Uint8 *res = malloc(image->height * sizeof(Uint8));
    Uint8 *ptr_res = res;

    for (int y = 0; y < image->height; y++) {
        ptr_res = &res[y];
        for (int x = 0; x < image->width; x++)
            *ptr_res += getPixelColor(image, x, y) == BLACK;
    }

    return res;
}

// @return the image's pixel histogram column per column
Uint8 *verticalHistogram(Image *image) {
    Uint8 *res = malloc(image->width * sizeof(Uint8));
    Uint8 *ptr_res = res;

    for (int x = 0; x < image->width; x++) {
        ptr_res = &res[x];
        for (int y = 0; y < image->height; y++)
            *ptr_res += getPixelColor(image, x, y) == BLACK;
    }

    return res;
}

void displayHisto(Image *image) {
    Uint8 *histo = horizontalHistogram(image);
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