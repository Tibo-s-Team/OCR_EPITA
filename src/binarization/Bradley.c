#include <stdio.h>
#include <stdlib.h>

#include "binarization.h"

void adaptativeThreshold(Image img, int w, int h, unsigned int out[w][h]);
//ToDo need to change everything for dynamically allocated memory arrays


void Bradley(char *filename, char *output)
{
    Image img = loadImage(filename);

    unsigned int *arr =  malloc(w * h * sizeof(unsigned int));

    adaptativeThreshold(img, img.width, img.height, out);

    for(int i = 0; i < img.width; i++)
    {
        for(int j = 0; j < img.height; j++)
            setPixelColor(&img, out[i][j], i, j);
    }
}


void adaptativeThreshold(Image img, int w, int h, unsigned int out[w][h])
{
    unsigned int *arr =  malloc(w * h * sizeof(unsigned int));

    int s = 12;
    int t = 15;

    for(int i = 0; i < w; i++)
    {
        unsigned long sum = 0;

        for(int j = 0; j < h; j++)
        {
            int pixelValue = getPixelColor(&img, i, j);
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

            int count = (x2-x1) * (y2-y1);
            int sum = intImage[x2][y2] - intImage[x2][y1-1] - intImage[x1-1][y2]
                + intImage[x1-1][y1-1];

            int pixel = getPixelColor(&img, i, j);
            if (pixel * count <= sum * (100-t)/100)
                out[i][j] = BLACK;
            else out[i][j] = WHITE;
        }
    }
}
