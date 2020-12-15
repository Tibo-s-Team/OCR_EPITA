/* File created on 1/12/2020 by lowen.desmarais
 *
 * contributors: lowen.desmarais
 *
 * File containing Otsu binarization function
 */

#include <stdlib.h>
#include <stdio.h>

#include "binarization.h"

//--------------------------------

void histogramGray(Image *img, unsigned long histogram[]);
unsigned long Threshold(unsigned long histogram[], Image *img);

//--------------------------------

/* Otsu function
 *
 * takes the pointer image and generates a gray histogram
 * then calculates the threshold value with it
 * and with this threshold recolorize the img
 * also changes the imageType to black and white
 * 
 * @param *img: the loaded image
 */

void Otsu(Image *img)
{
    unsigned long histogram[256] = {0, };

    histogramGray(img, histogram);
    unsigned long threshold = Threshold(histogram, img);

    for (int i = 0; i < img->width; i++)
    {
        for (int j = 0; j < img->height; j++)
        {
            Uint8 pixelValue = getPixelColor(img, i, j);
            if (pixelValue < threshold)
                setPixelColor(img, BLACK, i, j);
            else setPixelColor(img, WHITE, i, j);
        }
    }

    img->imageType = BW;
}

/* histogramGray function
 *
 * generates a histogram of grey pixel values of the image
 *
 * @param *img: pointer to loaded image
 * @param histogram: the array for the histogram
 */
void histogramGray(Image *img, unsigned long histogram[])
{
    for (int i = 0; i < img->width; i++)
    {
        for (int j = 0; j < img->height; j++)
        {
            histogram[getPixelColor(img, i, j)] += 1;
        }
    }
}

/* Threshold function
 *
 * calculates the threshold value by
 * using the total sum of the histogram
 * and for each pixel calculate the weight (values of the histogram
 * from 0 to i and from i to max)
 * then caclculates the means
 * and finally calculate the variance between sigma
 * returns the index (the grey value) when sigma maximum is found
 *
 * @param histogram: the grey histogram
 * @param *img: the pointer to the loaded image
 * @return: the determined threshold value
 */
unsigned long Threshold(unsigned long histogram[], Image *img)
{
    unsigned long totalPixel = img->width * img->height;

    float sum = 0;

    for (int i = 0; i < 256; i++)
        sum += i * histogram[i];

    float sumB = 0;
    int weightB = 0;
    int weightF = 0;

    float sigmaMax = 0;
    unsigned long thresholdMax = 0;

    for (int i = 0; i < 256; i++)
    {
	weightB += histogram[i];
	if (weightB == 0) continue;

	weightF = totalPixel - weightB;
	if (weightF == 0) break;

	sumB += i*histogram[i];

	float meanB = sumB/weightB;
	float meanF = (sum-sumB) / weightF;

	float sigmaBetween = weightB * weightF *(meanB-meanF) * 
		(meanB-meanF);

	if (sigmaBetween > sigmaMax)
	{
		sigmaMax = sigmaBetween;
		thresholdMax = i;
	}
	
    }

    return thresholdMax;
}
