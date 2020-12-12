#include <stdlib.h>
#include <stdio.h>

#include "binarization.h"


int main()
{
    Bradley("input/grayBradley.png", "output/Bradley.png");
    Otsu("input/grayOtsu.png", "output/Otsu.png");
    return 0;
}
