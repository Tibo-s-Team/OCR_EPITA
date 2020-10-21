#include "preprocessing.h"

#pragma region grayscale

void grayscale(Image *image) {
    Uint8 r, g, b, gray;

    if (image->imageType != RGB) return;
    image->imageType = GRAYSCALE;

    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            getPixelRGB(image, x, y, &r, &g, &b);
            // printf("%d|%d|%d\n", r, g, b);
            gray = 0.21 * r + 0.72 * g + 0.07 * b;  // grayscaling formula
            setPixelColor(image, gray, x, y);
            /*
            Uint32 pixel = get_pixel(image->surface, x, y);
            SDL_GetRGB(pixel, image->surface->format, &r, &g, &b);

            gray = 0.3 * r + 0.59 * g + 0.11 * b;
            pixel = SDL_MapRGB(image->surface->format, gray, gray, gray);

            put_pixel(image->surface, x, y, pixel);
            */
        }
    }
}

void grayscaleTest(Image *image) {
    const int WIDTH = image->width, HEIGHT = image->height;
    int count = 2;

    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *img = NULL;
    SDL_Rect texr;

    // create rendering context
    win = SDL_CreateWindow("Image Preview", 100, 100, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    // load image in the window
    img = SDL_CreateTextureFromSurface(renderer, image->surface);
    texr.x = 0;
    texr.y = 0;
    texr.w = WIDTH;
    texr.h = HEIGHT;

    while (count) {
        SDL_Event e;
        if (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT || e.type == SDL_KEYUP) {
                grayscale(image);
                count--;
            }

        // refresh renderer
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, img, NULL, &texr);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(img);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
}

#pragma endregion grayscale

#pragma region BW

void blackAndWhite(Image *image) {
    int seuil = 0;

    if (image->imageType == RGB)
        warnx(
            "Warning: supression_couleurs.c - blackAndWhite : imageType must "
            "be GRAYSCALE. Skipped.");
    else {
        for (int y = 0; y < image->height; y++) {
            for (int x = 0; x < image->width; x++) {
                Uint8 color = getPixelColor(image, x, y);
                seuil += color;
            }
        }
        seuil = seuil / (image->width * image->height);
        for (int y = 0; y < image->height; y++) {
            for (int x = 0; x < image->width; x++) {
                Uint8 color = getPixelColor(image, x, y);
                color = color <= seuil ? BLACK : WHITE;
                setPixelColor(image, color, x, y);
            }
        }
    }

    image->imageType = BW;
}

#pragma endregion BW
