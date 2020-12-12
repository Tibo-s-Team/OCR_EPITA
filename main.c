#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/image.h"
#include "src/preprocessing/preprocessing.h"
#include "src/segmentation/segmentation.h"

int main(int argc, char *argv[]) {
    Image image;

    static int gray = 0;
    static int black_and_white = 0;
    static int lines = 0;
    static int display = 0;

    if (argc < 2)  // if no path given do nothing
        return 0;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_NUMEVENTS) < 0) {
        printf("Error: failed to initialize SDL: %s", SDL_GetError());
        return 1;
    } else {
        for (int i = 1; i < argc; i++)  // for all given paths
        {
            image = loadImage(argv[i]);

            grayscale(&image);
            blackAndWhite(&image);

            // segmentation(&image);
            // bin_segmentation(&image);
            // displayImage(&image);

            BBox area = {(Pixel){100, 100}, (Pixel){image.width / 4, image.height / 4}};
            extractImage(&image, "test.png", area);

            IMG_Quit();
        }
    }

    return 0;
}
