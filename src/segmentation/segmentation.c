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
 *  12/11 : Abandonned binaryTree for a simple boundaryBox struct.
 *  Need to fix threshold calculation
 *
 * //TODO : implement better thresholding system
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
            int *letters = segmentLetters(image, height, width);

            for (int letter = 1; letter < letters[0]; letters += 2) {
                int tmp[2] = {letters[letter], letters[letter + 1]};
                highlightText(image, height, tmp);
            }
            free(letters);
        }
        free(words);
    }
    free(lines);
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
 * BoundaryBox : holds coordinates of the detected text.
 *
 * 12/11/2020 : BinaryTree dropped, created boundarybox struct instead.
 */

//--------------------------------------------

Pixel *bin_findBoxes(Histogram *histo, size_t *len);
void bin_highlightText(Image *image, BBox box);
Pixel *getColumns(Image *image, BBox line, size_t *len);
void printBox(BBox box);

//--------------------------------------------

/*!
 * Apply segmentation process to a given image using the !boundaryBox
 *  implementation.
 * @param image black and white image
 */
void bin_segmentation(Image *image) {
    if (image->imageType != BW)
        errx(1,
             "ERROR : segmentation.c - segmentLine : Image must have been "
             "binarized beforehand.\n");

    Histogram histo = lineHistogram(image);
    size_t len;

    // x = start of box | y = end of box
    Pixel *lines = bin_findBoxes(&histo, &len);

    for (size_t i = 0; i < len; i++) {
        BBox line = {(Pixel){0, lines[i].x}, (Pixel){image->width, lines[i].y}};

        size_t word_count;
        Pixel *words = getColumns(image, line, &word_count);

        for (size_t j = 0; j < word_count; j++) {
            BBox word = {(Pixel){words[j].x, line.start.y},
                         (Pixel){words[j].y, line.end.y}};

            size_t letter_count;
            Pixel *letters = getColumns(image, word, &letter_count);

           
            // temporary, we should delete files afterwards
            char *file = (char *)calloc(40, sizeof(char));
            sprintf(file, "images/%ld_%ld.png", i, j);
            extractImage(image, file, word);
            free(file);

            for (size_t z = 0; z < letter_count; z++) {
                BBox letter = {(Pixel){letters[j].x, line.start.y},
                               (Pixel){letters[j].y, line.end.y}};
                // FIXME : fix threshold pls important
            }
            free(letters);
        }
        free(words);
    }
    free(lines);
}

/*!
 * Highlight text in an image. Mainly used for test purposes.
 * @param image black and white image
 * @param tree BoundaryBox representing the area to highlight in the image
 */
void bin_highlightText(Image *image, BBox box) {
    for (int y = box.start.y; y < box.end.y; y++) {
        for (int x = box.start.x; x < box.end.x; x++)
            setPixelColor(image, BLACK, x, y);
    }
}

/*!
 * Segement a box into columns (line to words / word to letters).
 * @param image black and white image
 * @param line BoundaryBox we want to segment.
 * @param len pointer used to store the number of resulting columns.
 */
Pixel *getColumns(Image *image, BBox line, size_t *len) {
    int columnBlock[2] = {line.start.x, line.end.x},
        lineBlock[2] = {line.start.y, line.end.y};
    Histogram histo = columnHistogram(image, lineBlock, columnBlock);

    // x = start of box | y = end of box
    Pixel *boxes = bin_findBoxes(&histo, len);
    return boxes;
}

/*!
 * Find all 'boxes' in a given histogram.
 * @return a list of all the identified boundary boxes
 * @param histo the histogram
 * @param len pointer to the size of the returned list
 */
Pixel *bin_findBoxes(Histogram *histo, size_t *len) {
    // BinTree res = createBinTree(0, 0);  // generic tree to append to
    int gap = 0, size = 0;
    *len = 0;

    // Store nodes in an array instead of local stack
    Pixel *boxes = calloc(histo->size, sizeof(Pixel));

    for (int i = 0; i < histo->size; i++) {
        int line = histo->histo[i];
        if (line >= histo->mean)
            ++size;
        else {
            if (size > 0) {  // if we just quit a block
                if (gap > histo->threshold[0] && size > histo->threshold[1]) {
                    // append block if it is of the correct size
                    boxes[*len] = (Pixel){i - size - 1, i - 1};
                    *len += 1;
                }
                gap = 0;
                size = 0;
            }
            gap++;
        }
    }
    // check if still in a block when exiting the loop
    if (size > 0 && gap > histo->threshold[0] && size > histo->threshold[1]) {
        boxes[*len] = (Pixel){histo->size - size - 1, histo->size - 1};
        *len += 1;
    }

    return boxes;
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
    int mean = 0, size = image->width;
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
