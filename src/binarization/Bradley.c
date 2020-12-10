#include <stdio.h>
#include <stdlib.h>

#include "binarization.h"

void adaptativeThreshold(Image img, unsigned int out[], int w, int h);


void Bradley(char *filename, char *output)
{
    Image img = loadImage(filename);
    unsigned int out[img.width][img.height] = {
        {0, },
    };

    adaptativeThreshold(img, out, img.width, img.height);

    for(int i = 0; i < img.width; i++)
    {
        for(int j = 0; j < img.height; j++)
            setPixelColor(img, out[i][j], i, j)
    }

    displayImage(img);
}


void adaptativeThreshold(Image img, unsigned int out[], int w, int h)
{
    unsigned long intImage[w][h] = {
        {0, },
    };

    int s = 12;
    int t = 15;

    for(int i = 0; i < w; i++)
    {
        unsigned long sum = 0;

        for(int j = 0; j < h; j++)
        {
            int pixelValue = getPixelColor(img, i, j);
            sum += pixelValue;

            if (i == 0) intImage[i][j] = sum;
            else intImage[i][j] = intImage[i-1][j] + sum;
        }
    }

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            int surrounding = s/2;
            int x1 = (i < surrounding) ? i-surrounding : 0;
            int x2 = (i+surrounding < w) ? i+surrounding : w-1;
            int y1 = (j < surrounding) ? j - surrounding : 0;
            int y2 = (j + surrounding < h) ? j+surrounding : h-1;

            count = (x2-x1) * (y2-y1);
            sum = intImage[x2][y2] - intImage[x2][y1-1] - intImage[x1-1][y2]
                + intImage[x1-1][y1-1];

            int pixel = getPixelColor(img, i, j);
            if (pixel * count <= sum * (100-t)/100)
                out[i][j] = BLACK;
            else out[i][j] = WHITE;
        }
    }
}
