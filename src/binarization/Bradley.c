/* File created on 1/12/2020 by lowen.desmarais
 * 
 * contributors: lowen.desmarais
 *
 * File containing Bradley binarization
 */

#include <stdio.h>
#include <stdlib.h>

#include "binarization.h"

//----------------------------------

void adaptativeThreshold(Image *img, int w, int h, unsigned int **out);

//----------------------------------

/* Bradley
 * takes the pointer Image
 * calculates the threshold with the integral image and fill "out"
 * recolorize the image with the values from "out"
 * also changes the imageType value to black and white
 * @param *img: the image loaded
 */

void Bradley(Image *img)
{
    unsigned int** out = malloc(img->height * sizeof *out);
    for (int i = 0; i < img->height; ++i) out[i] = calloc(img->width , sizeof *out[i]);

    
    adaptativeThreshold(img, img->width, img->height, out);

    for(int i = 0; i < img->width; i++)
    {
        for(int j = 0; j < img->height; j++)
            setPixelColor(img, out[j][i], i, j);
    }

    img->imageType = BW;
}

/* adapatativeThreshold
 *
 * creates and fills the integral image
 * then calculates the threshold value for each pixel
 * with s as the surrounding pixel square surface
 * and t the percentage value for the square surface
 * then fills "out" with the new values
 *
 * @param *img: the loaded image
 * @param w: the width of the image
 * @param h: the height of the image
 * @param out: the array with the new pixel values after thesholding
 */

void adaptativeThreshold(Image *img, int w, int h, unsigned int **out)
{
    int** intImage = malloc(h * sizeof *intImage);
    for (int i = 0; i < h; ++i) intImage[i] = calloc(w , sizeof *intImage[i]);

    int s = w/32;
    int t = 20;

    for(int i = 0; i < w; i++)
    {
        unsigned long sum = 0;

        for(int j = 0; j < h; j++)
        {
            int pixelValue = getPixelColor(img, i,j);
            sum += pixelValue;

            if (i == 0) intImage[j][i] = sum;
            else intImage[j][i] = intImage[j][i-1] + sum;
        }
    }

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            int surrounding = s/2;
            int x1 = (i >= surrounding) ? i-surrounding : 0;
            int x2 = (i+surrounding < w) ? i+surrounding : w-1;
            int y1 = (j >= surrounding) ? j - surrounding : 0;
            int y2 = (j + surrounding < h) ? j+surrounding : h-1;

            int count = (x2-x1) * (y2-y1);

            int sum = intImage[y2][x2] - intImage[y2][x1] - intImage[y1][x2]
                + intImage[y1][x1];

            int pixel = getPixelColor(img, i, j);
            if (pixel * count <= sum * (100-t)/100)
                out[j][i] = BLACK;
            else out[j][i] = WHITE;
        }
    }
}
