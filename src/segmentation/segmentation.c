/*!
 *  This file implements the text block segmentation process using an histogram
 * based algorithm. Computing a pixel histogram for each line / column then
 * finding "blocks" of empty spaces within these histograms. The file is then
 * separated in smaller images.
 */

#include "segmentation.h"

//---------------------------------------------

Histogram columnHistogram(Image *image);
Histogram lineHistogram(Image *image);
int *findBlocks(Histogram *histo);

//---------------------------------------------

// Highlights what the algorithm thinks is a line
void segmentLine(Image *image) {
    if (image->imageType != BW)
        errx(1,
             "ERROR : segmentation.c - segmentLine : Image must have been "
             "binarized beforehand.\n");

    Histogram histo = lineHistogram(image);
    int *blocks = findBlocks(&histo);
    int length = blocks[0];

    for (int i = 1; i < length; i += 2) {
        int start = blocks[i], end = blocks[i + 1];
        for (int y = start; y <= end; y++) {
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
        histo, LINE, {0, 0}, mean / (2 * image->height), image->height};
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
        histo, COLUMN, {0, 0}, mean / (2 * image->width), image->height};
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
int *findBlocks(Histogram *histo) {
    // TODO threshold system (currently set to 0)
    int *blocks = calloc(histo->size + 1, sizeof(int));
    int gap = 0, size = 0, blocks_index = 1;
    // Length of the array set to 1 (the size value itself)
    blocks[0] = 1;

    for (int i = 0; i < histo->size; i++) {
        int line = histo->histo[i];
        if (line >= histo->mean)  // if currently in a block
            ++size;
        else {
            if (size > 0) {
                if (gap > histo->threshold[0] && size > histo->threshold[1]) {
                    blocks[blocks_index++] = i - size - 1;  // start
                    blocks[blocks_index++] = i - 1;         // end
                    blocks[0] += 2;                         // update array size
                }
                gap = 0;
                size = 0;
            }
            gap++;
        }
    }
    if (size > 0 && gap > histo->threshold[0] && size > histo->threshold[1]) {
        blocks[blocks_index++] = histo->size - size - 1;  // start
        blocks[blocks_index++] = histo->size - 1;         // end
        blocks[0] += 2;                                   // update array size
    }

    return blocks;
}

#pragma region BinTree

//--------------------------------------------

BinTree bin_findBlocks(Histogram *histo);

//--------------------------------------------

void bin_segmentLine(Image *image) {
    if (image->imageType != BW)
        errx(1,
             "ERROR : segmentation.c - segmentLine : Image must have been "
             "binarized beforehand.\n");

    Histogram histo = lineHistogram(image);
    BinTree blocks = bin_findBlocks(&histo);

    // TODO
    // apply segmentation to all he leaves of the tree
    // add the resulting tree as their child.
}

BinTree bin_findBlocks(Histogram *histo) {
    BinTree res = createBinTree(0, 0);
    int gap = 0, size = 0, blocks_index = 1;

    for (int i = 0; i < histo->size; i++) {
        int line = histo->histo[i];
        if (line >= histo->mean)
            ++size;
        else {
            if (size > 0) { // if we just quit a block
                if (gap > histo->threshold[0] && size > histo->threshold[1]) {
                    // if block is of the correct size -> append it in a new node.
                    BinTree node = createBinTree(i - size - 1, i - 1);
                    appendBinTree(&node, &res);
                }
                gap = 0;
                size = 0;
            }
            gap++;
        }
    }
    // check if still in a block when exiting the loop
    if (size > 0 && gap > histo->threshold[0] && size > histo->threshold[1]) {
        BinTree node = createBinTree(histo->size - size - 1, histo->size - 1);
        appendBinTree(&node, &res);
    }

    return *res.sibling;
}

#pragma endregion BinTree
