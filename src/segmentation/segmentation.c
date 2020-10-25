/*!
 *  File created on 10/15/2020 (MM/DD/YYYY) by leo.duboin
 *  Contributors : leo.duboin
 *
 *  This file implements the text block segmentation process using an histogram
 *  based algorithm. Computing a pixel histogram for each line / column then
 *  finding "blocks" of empty spaces within these histograms.
 *
 *  10/23 : Implementation of a binaryTree data structure to store all the
 *  boundary boxes.
 *
 * //TODO : Fix letter segmentation, implement threshold system
 */

#include "segmentation.h"

#pragma region ArrayImplementation

//---------------------------------------------

void highlightText(Image *image, int height[2], int width[2]);

int *segmentLine(Image *image);
int *segmentWords(Image *image, int line[2]);
int *segmentLetters(Image *image, int line[2], int column[2]);

Histogram columnHistogram(Image *image, int lineBlock[2], int columnBLock[2]);
Histogram lineHistogram(Image *image);
int *findBlocks(Histogram *histo);

//---------------------------------------------

/*!
 * Apply segmentation process to a given image using the classic array
 *  implementation.
 * @param image black and white image
 */
void segmentation(Image *image) {
    if (image->imageType != BW)
        errx(1,
             "ERROR : segmentation.c - segmentLine : Image must have been "
             "binarized beforehand.\n");

    int *lines = segmentLine(image);

    for (int line = 1; line < lines[0]; lines += 2) {
        int height[2] = {lines[line], lines[line + 1]};
        int *words = segmentWords(image, height);
        for (int word = 1; word < words[0]; word += 2) {
            int width[2] = {words[word], words[word + 1]};
            highlightText(image, height, width);
        }
    }
}

/*!
 * Apply line segmentation process to a given image using the classic array
 *  implementation.
 * @param image black and white image
 */
void lineSegmentation(Image *image) {
    if (image->imageType != BW)
        errx(1,
             "ERROR : segmentation.c - segmentLine : Image must have been "
             "binarized beforehand.\n");

    int *lines = segmentLine(image);

    for (int line = 1; line < lines[0]; lines += 2) {
        int height[2] = {lines[line], lines[line + 1]};
        int width[2] = {0, image->width};
        highlightText(image, height, width);
    }
}

/*!
 * Highlight text in an image.
 * @param image black and white image
 * @param height tuple with information about the text's height (start, end)
 * @param width tuple with information about the text's width (start, end)
 */
void highlightText(Image *image, int height[2], int width[2]) {
    for (int y = height[0]; y < height[1]; y++) {
        for (int x = width[0]; x < width[1]; x++)
            setPixelColor(image, BLACK, x, y);
    }
}

/*!
 * Segment an image into lines.
 * @param image black and white image
 * @returns An array of the form [size, (start, end), ..., (start, end)]
 *  where each tuple represent the start and the end of a line, size being the
 *  total size of the resulting array.
 */
int *segmentLine(Image *image) {
    // FIXME
    Histogram histo = lineHistogram(image);
    int *blocks = findBlocks(&histo);

    return blocks;
}

/*!
 * Segment a line into words.
 * @param image black and white image
 * @param line tuple representing the starting and the ending height of the line
 *  to segment
 * @returns An array of the form [size, (start, end), ..., (start, end)]
 *  where each tuple represent the starting and the ending width of a word, size
 *  being the total size of the resulting array.
 */
int *segmentWords(Image *image, int line[2]) {
    int column[2] = {0, image->width};
    Histogram histo = columnHistogram(image, line, column);
    int *blocks = findBlocks(&histo);

    return blocks;
}

/*!
 * Segment a word into letters.
 * @param image black and white image
 * @param line tuple representing the start and the end width of the line
 *  containing the word
 * @param word tuple representing the startign and the ending width of the word
 * @returns An array of the form [size, (start, end), ..., (start, end)]
 *  where each tuple represent the starting and the ending width of a word, size
 *  being the total size of the resulting array.
 */
int *segmentLetters(Image *image, int line[2], int word[2]) {
    Histogram histo = columnHistogram(image, line, word);
    int *blocks = findBlocks(&histo);

    return blocks;
}

/*!
 * @returns An array of the form [size, (start, end), ..., (start, end)]
 *  with each tuple representing the starting and the ending position of a
 *  block, size being the total size of the resulting array.
 */
int *findBlocks(Histogram *histo) {
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

#pragma endregion Array

#pragma region BinTreeImplementation

/*!
 * The same algorithm but making use of a binary tree to store the boxes.
 * You apply segmentation to its leaves and add the resulting boxes as their
 * child.
 *
 * Current Issue : pointers are acting weird with local variables
 */

//--------------------------------------------

BinTree bin_findBlocks(Histogram *histo);
void bin_highlightText(Image *image, BinTree *tree);
void bin_test(Image *image, BinTree *tree);
void getLines(Image *image, BinTree *node);

//--------------------------------------------

/*!
 * Apply segmentation process to a given image using the binary tree
 *  implementation.
 * @param image black and white image
 */
void bin_segmentation(Image *image) {
    if (image->imageType != BW)
        errx(1,
             "ERROR : segmentation.c - segmentLine : Image must have been "
             "binarized beforehand.\n");

    // TODO
    // apply segmentation to all he leaves of the tree
    // add the resulting tree as their child.

    BinTree node = createBinTree(0, image->height);
    getLines(image, &node);
    mapFunction(&node, image, bin_highlightText);
}

/*!
 * Highlight text in an image.
 * @param image black and white image
 * @param tree a tree node whose key contains information about
 *  the text's position in the image
 */
void bin_highlightText(Image *image, BinTree *tree) {
    int start = tree->key[0], end = tree->key[1];

    for (int y = start; y < end; y++) {
        for (int x = 0; x < image->width; x++)
            setPixelColor(image, BLACK, x, y);
    }
}

/*!
 * Segement an image into lines and add them as the given node's children.
 * @param image black and white image
 * @param node root of the image's 'box' binary tree
 */
void getLines(Image *image, BinTree *node) {
    Histogram histo = lineHistogram(image);
    BinTree child = bin_findBlocks(&histo);
    addChild(&child, node);
}

/*!
 * Find all the 'box' in a given histogram.
 * @return a binary tree forest whose tree's keys contain the starting and
 *  ending position of all the boxes found.
 */
BinTree bin_findBlocks(Histogram *histo) {
    BinTree res = createBinTree(0, 0);  // generic tree to append to
    int gap = 0, size = 0, blocks_index = 1;

    // Store nodes in an array instead of local stack
    BinTree *nodes = calloc(histo->size + 1, sizeof(BinTree));

    for (int i = 0; i < histo->size; i++) {
        int line = histo->histo[i];
        if (line >= histo->mean)
            ++size;
        else {
            if (size > 0) {  // if we just quit a block
                if (gap > histo->threshold[0] && size > histo->threshold[1]) {
                    // if block is of the correct size -> append it in a new
                    // node
                    nodes[i] = createBinTree(i - size - 1, i - 1);
                    addSibling(&nodes[i], &res);
                }
                gap = 0;
                size = 0;
            }
            gap++;
        }
    }
    // check if still in a block when exiting the loop
    if (size > 0 && gap > histo->threshold[0] && size > histo->threshold[1]) {
        nodes[histo->size] =
            createBinTree(histo->size - size - 1, histo->size - 1);
        addSibling(&nodes[histo->size], &res);
    }

    free(nodes);
    return res;
}

#pragma endregion BinTree

#pragma region histogram

/*!
 * @return the image's pixel histogram, line per line
 */
Histogram lineHistogram(Image *image) {
    int mean = 0, size = image->height;
    int *histo = calloc(size, sizeof(int));
    int *ptr_histo = histo;

    for (int y = 0; y < image->height; y++) {
        ptr_histo = &histo[y];
        for (int x = 0; x < image->width; x++)
            *ptr_histo += getPixelColor(image, x, y) == BLACK;
        if (*ptr_histo < (100 * size) / 85) mean += *ptr_histo;
    }

    Histogram res = {histo, LINE, {0, 0}, mean / (2 * size), size};
    return res;
}

/*!
 * @return the image's pixel histogram, column per column
 */
Histogram columnHistogram(Image *image, int lineBlock[2], int columnBLock[2]) {
    int mean = 0, size = columnBLock[1] - columnBLock[0];
    int *histo = calloc(size, sizeof(int));
    int *ptr_histo = histo;

    for (int x = columnBLock[0]; x < columnBLock[1]; x++) {
        ptr_histo = &histo[x];
        for (int y = lineBlock[0]; y < lineBlock[1]; y++)
            *ptr_histo += getPixelColor(image, x, y) == BLACK;
        if (*ptr_histo < (100 * size) / 85) mean += *ptr_histo;
    }

    Histogram res = {histo, COLUMN, {0, 0}, mean / (2 * size), size};
    return res;
}

#pragma endregion histogram
