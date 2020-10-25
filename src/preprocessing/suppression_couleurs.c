/*!
 *  File created on 10/10/2020 (MM/DD/YYYY) by leo.duboin
 *  Contributors : leo.duboin
 *
 *  File containing the necessary functions to binarize an image.
 * 
 *  10/20 : Modified version using the new image.c functions
 */

#include "preprocessing.h"

/*!
 * Apply grayscaling algorithm onto an image.
 * @param image RGB image
 */
void grayscale(Image *image) {
    Uint8 r, g, b, gray;

    if (image->imageType != RGB) return;
    image->imageType = GRAYSCALE;

    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            getPixelRGB(image, x, y, &r, &g, &b);
            gray = 0.21 * r + 0.72 * g + 0.07 * b;  // grayscaling formula
            setPixelColor(image, gray, x, y);
        }
    }
}

/*!
 * Apply binarization onto an already grayscaled image.
 * @param image grayscaled image
 */
void blackAndWhite(Image *image) {
    int seuil = 0;

    if (image->imageType == RGB)
        warnx(
            "Warning: supression_couleurs.c - blackAndWhite : imageType must "
            "be GRAYSCALE. Skipped.");
    else {
        for (int y = 0; y < image->height; y++) {
            for (int x = 0; x < image->width; x++) {
                Uint8 color = getPixelColor(image, x, y);
                seuil += color;
            }
        }
        seuil = seuil / (image->width * image->height);
        for (int y = 0; y < image->height; y++) {
            for (int x = 0; x < image->width; x++) {
                Uint8 color = getPixelColor(image, x, y);
                color = color <= seuil ? BLACK : WHITE;
                setPixelColor(image, color, x, y);
            }
        }
    }

    image->imageType = BW;
}
