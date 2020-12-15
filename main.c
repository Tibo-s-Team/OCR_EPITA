#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/binarization/binarization.h"
#include "src/Image/image.h"
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

    if (SDL_Init(SDL_INIT_VIDEO | SDL_GETEVENT) < 0) {
        printf("Error: failed to initialize SDL: %s", SDL_GetError());
        return 1;
    } else {
        for (int i = 1; i < argc; i++)  // for all given paths
        {
            if (argv[i][0] == '-') {
                for (int j = 1; j < (int)strlen(argv[i]); j++) {
                    switch (argv[i][j]) {
                        case 'd':
                            display = 1;
                            break;
                        case 'g':
                            gray = 1;
                            break;
                        case 'b':
                            gray = 1;
                            black_and_white = 1;
                            break;
                        case 'l':
                            gray = 1;
                            black_and_white = 1;
                            lines = 1;
                            break;
                        default:
                            break;
                    }
                }
            } else {
                Image image = loadImage(argv[i]);
                int words = !gray && !black_and_white && !lines;

                if (!display) {
                    if (gray || words) grayscale(&image);
                    if (black_and_white || words) Bradley(&image);
                    image.imageType = BW;
                    if (lines || words) {
                        //filterImage(&image, SHARPNESS);
                        blackAndWhite(&image);
                        bin_segmentation(&image);
                    }
                }

                displayImage(&image);
            }
        }
    }

    return 0;
}
