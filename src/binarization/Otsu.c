#include <stdlib.h>
#include <stdio.h>

#include "binarization.h"


void histogramGray(Image img, unsigned long histogram[]);
unsigned long Threshold(unsigned long histogram[], Image img);

void Otsu(char *filename, char *output)
{
    Image img = loadImage(filename);
    
    unsigned long histogram[256] = {0, };

    histogramGray(img, histogram);
    unsigned long threshold = Threshold(histogram, img);

    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            Uint8 pixelValue = getPixelColor(&img, i, j);
            if (pixelValue < threshold)
                setPixelColor(&img, BLACK, i, j);
            else setPixelColor(&img, WHITE, i, j);
        }
    }

    displayImage(&img);

}

void histogramGray(Image img, unsigned long histogram[])
{
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            histogram[getPixelColor(&img, i, j)] += 1;
        }
    }
}

unsigned long Threshold(unsigned long histogram[], Image img)
{
    unsigned long totalPixel = img.width * img.height;

    unsigned long omega = 0;
    unsigned long mu = 0;
    unsigned long muT = 0;

    for (int i = 0; i < 256; i++)
        muT += i * (histogram[i] / totalPixel);

    unsigned long thresholdMax = 0;
    for (int i = 0; i < 256; i++)
    {
        omega += histogram[i] / totalPixel;
        mu += i * (histogram[i] / totalPixel);

        unsigned long temp = (muT*omega) - mu;
        unsigned long sigma = (temp*temp) / (omega * (1-omega));

        if (sigma > thresholdMax)
            thresholdMax = i;
    }

    return thresholdMax;
}
