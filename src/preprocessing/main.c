#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../binarization/binarization.h"
#include "preprocessing.h"

int main(int argc, char const *argv[]) {
    Image image;

    if (argc < 2)  // if no path given do nothing
        return 0;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_GETEVENT) < 0) {
        printf("Error: failed to initialize SDL: %s", SDL_GetError());
        return 1;
    } else {
        for (int i = 1; i < argc; i++)  // for all given paths
        {
            image = loadImage(argv[i]);

            grayscale(&image);
            Bradley(&image);

            filterImage(&image, SHARPNESS);
            filterImage(&image, SHARPNESS);

            blackAndWhite(&image);
            displayImage(&image);

            Bradley(&image);

            IMG_Quit();
        }
    }

    return 0;
}
