#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "src/image.h"
#include "src/preprocessing.h"

int main(int argc, char *argv[]) {
    Image image;

    if (argc < 2)  // if no path given do nothing
        return 0;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        printf("Error: failed to initialize SDL: %s", SDL_GetError());
        return 1;
    } else {
        for (int i = 1; i < argc; i++)  // for all given paths
        {
            image = loadImage(argv[i]);
            grayscaleImage(&image);
            blackAndWhite(&image);
            displayImage(&image);  // test
            IMG_Quit();
        }
    }

    return 0;
}
