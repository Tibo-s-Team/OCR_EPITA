#include <stdio.h>
#include <stdlib.h>

#include "binarization.h"

void adaptativeThreshold(Image img, int w, int h, unsigned int **out);


void Bradley(Image img)
{
    unsigned int** out = malloc(img.height * sizeof *out);
    for (int i = 0; i < img.height; ++i) out[i] = calloc(img.width , sizeof *out[i]);

    
    adaptativeThreshold(img, img.width, img.height, out);

    for(int i = 0; i < img.width; i++)
    {
        for(int j = 0; j < img.height; j++)
            setPixelColor(&img, out[j][i], i, j);
    }

    img.imageType = BW;
}


void adaptativeThreshold(Image img, int w, int h, unsigned int **out)
{
    int** intImage = malloc(h * sizeof *intImage);
    for (int i = 0; i < h; ++i) intImage[i] = calloc(w , sizeof *intImage[i]);

    int s = 30;
    int t = 15;

    for(int i = 0; i < w; i++)
    {
        unsigned long sum = 0;

        for(int j = 0; j < h; j++)
        {
            int pixelValue = getPixelColor(&img, i,j);
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

            int pixel = getPixelColor(&img, i, j);
            if (pixel * count <= sum * (100-t)/100)
                out[j][i] = BLACK;
            else out[j][i] = WHITE;
        }
    }
}
