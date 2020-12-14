#include <stdlib.h>
#include <stdio.h>

#include "binarization.h"
#include "../preprocessing/preprocessing.h"


int main()
{
    Image img = loadImage("images/otsuGray.jpg");
    //Image img = loadImage("images/hh.png");
    grayscale(&img);
    displayImage(&img);
    //Bradley(img);
    Otsu(img);
    displayImage(&img);
    return 0;
}
