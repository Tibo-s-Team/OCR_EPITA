/*!
 *  File created on 10/12/2020 (MM/DD/YYYY) by leo.duboin
 *  Contributors : leo.duboin
 *
 *  File containing the necessary functions to apply filters onto an image.
 *  You should normally use the SHARPNESS filter as it is the most efficient.
 *
 * Remark : You should always rebinarize your image afterwards as the resulting
 * values may differ from 0 or 255. The basic B&W function works generraly
 * better.
 *
 *  12/13/2020 : added gaussian filter (bugged) + fixed convolution
 *  12/14/2020 : added median filtering + external funtion call handler
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "preprocessing.h"
#include "utils.h"

//--------------------------------
// median
void medianFiltering(Image *image);
// convolution
void convolution(Image *image, Kernel (*f)());
void convolutePixel(Image *image, Kernel kernel, int x, int y);
void reverseKernel(Kernel kernel);
//--------------------------------

/*!
 * Apply a filter onto an image. 
 * Main function to call outside the file. 
 * @warning You may want to rebinarize your image afterwards
 * @param image the image to apply the filter onto
 * @param filter the filter we want to apply
 */
void filterImage(Image *image, Filter filter) {
    if (image->imageType == RGB)
        errx(1,
             "Error: filtrage.c: filterImage - "
             "image must not be of type RGB.");

    switch (filter) {
        case AVERAGE:
            convolution(image, averageFilter);
            break;
        case CONTOURS:
            convolution(image, contoursFilter);
            reverseColor(image);
            break;
        case SHARPNESS:
            convolution(image, sharpnessFilter);
            reverseColor(image);
            break;
        case EDGE:
            convolution(image, edgeFilter);
            reverseColor(image);
            break;
        case SOBEL:
            convolution(image, sobelFilter);
            break;
        case GAUSSIAN:
            convolution(image, gaussianFilter);
            break;
        case MEDIAN:
            medianFiltering(image);
            break;
        default:
            errx(1, "Error: filtrage.c: filterImage: invalid filter type.");
            break;
    }

    // Values may not all be between 0 and 255, so just to make sure
    image->imageType = GRAYSCALE;
}

#pragma region filtering

/*!
 * Apply convolution onto an image using a given kernel
 * @param image the image to apply convolution onto
 * @param f the function returning the kernel to use
*/
void convolution(Image *image, Kernel (*f)()) {
    Kernel kernel = (*f)();
    reverseKernel(kernel);
    int center = kernel.size / 2;

    for (int y = center; y < image->height - center; ++y) {
        for (int x = center; x < image->width - center; ++x) {
        }
    }
}

/*!
 * Apply convolution to a given pixel
 * @param image the image we want to apply convolution to
 * @param kernel the kernel we use for the convolution (already reversed !)
 */
void convolutePixel(Image *image, Kernel kernel, int x, int y) {
    // place chosen pixel in the center of the kernel
    int center = kernel.size / 2;
    if (x < center || y < center)
        errx(1,
             "Error: filtrage.c : convolutePixel - "
             "Pixel coordinate doesn't fit, (%d,%d) with a kernel of size %d",
             x, y, kernel.size);
    if (x > image->width - center || y > image->height - center)
        errx(1,
             "Error: filtrage.c : convolutePixel - "
             "Pixel coordinate doesn't fit, (%d,%d) with a kernel of size %d "
             "and image of size %dx%d",
             x, y, kernel.size, image->width, image->height);

    int pixel = 0;

    for (int i = 0; i < kernel.size; ++i) {
        for (int j = 0; j < kernel.size; ++j) {
            // multiplier les elements correpondants (k[i,j] *
            // pixels[x-1+i,y-1+j]) additioner tous les resultats des
            // multiplications
            int I = i - center, J = j - center;
            int value = kernel.matrix[(kernel.size * i) + j];
            Uint8 color = getPixelColor(image, x + J, y + I);
            // printf("%d * %d\n", value, color);

            pixel += value * color;
        }
    }

    pixel /= kernel.size * kernel.size;
    setPixelColor(image, (Uint8)pixel, x, y);
}

/*!
 * Reverse the columns and the lines of a kernel (matrix).
 * [ [0,1],[2,3] ] => [ [3,2],[1,0] ]
 * @param kernel the kernel whose columns/lines we want to inverse
 */
void reverseKernel(Kernel kernel) {
    int total_size = kernel.size * kernel.size;
    for (int i = 0; i < total_size / 2; ++i) {  // swap doesn't work here idk why
        int a = kernel.matrix[i], b = kernel.matrix[total_size - i - 1];
        kernel.matrix[i] = b;
        kernel.matrix[total_size - i - 1] = a;
    }
}

/*!
 * Apply median filtering onto an image.
 * @param image the image to apply filter onto
 */
void medianFiltering(Image *image) {
    if (image->imageType == RGB)
        errx(1,
             "Error: filtrage.c: medianFiltering: "
             "given image is of RGB type.");

    int size = 3;
    int center = size / 2;

    for (int y = center; y < image->height - center; ++y) {
        for (int x = center; x < image->width - center; ++x) {
            Uint8 color = medianFilter(image, size, x, y);
            setPixelColor(image, color, x, y);
        }
    }
}

#pragma endregion filtering
