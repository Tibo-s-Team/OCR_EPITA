#include "image.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

Image loadImage(const char *path) {
    SDL_Surface *surface = NULL;
    Image image;

    int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    int initted = IMG_Init(flags);
    if ((initted & flags) != flags) {
        printf(
            "ERROR: image_loading.c - could not init required image format "
            "(jpg, png)\n");
        printf("%s", IMG_GetError());
    } else {
        surface = IMG_Load(path);
        if (surface == NULL)
            printf("ERROR: image_loading.c - %s\n", IMG_GetError());
        else {
            image.surface = surface;
            image.width = surface->w;
            image.height = surface->h;
            image.imageType = RGB;
        }
    }

    return image;
}

void displayImage(Image *image) {
    const int WIDTH = image->width, HEIGHT = image->height;

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

    while (1) {
        SDL_Event e;
        if (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT)  // escape key
                break;

        // refresh renderer
        SDL_RenderClear(renderer);                   // clear the screen
        SDL_RenderCopy(renderer, img, NULL, &texr);  // save renderer
        SDL_RenderPresent(renderer);                 // update renderer
    }

    SDL_DestroyTexture(img);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
}

void grayscaleImage(Image *image) {
    SDL_Surface *surface = NULL;
    Uint8 *pixels = NULL;

    surface = image->surface;
    pixels = (Uint8 *)surface->pixels;

    if (image->imageType != RGB || surface->format->BytesPerPixel == 1) return;

    int locked = SDL_MUSTLOCK(surface);
    if (!locked) SDL_LockSurface(surface);

    grayscale32(pixels, surface->format, image->width, image->height,
                surface->pitch);
    image->imageType = GRAYSCALED;

    if (!locked) SDL_UnlockSurface(surface);
}

void grayscale32(Uint8 *pixels, SDL_PixelFormat *format, int width, int height,
                 int pitch) {
    Uint32 *targetPixel = NULL;
    Uint8 r, g, b, gray;
    printf("%d", pitch);

    for (int y = 0; y * pitch < height * width * 3; y++) {
        for (int x = 0; x < pitch / 4; x++) {
            targetPixel = 
                pixels + y * pitch + x * sizeof(*targetPixel);
            SDL_GetRGB(*targetPixel, format, &r, &g, &b);
            gray = 0.21 * r + 0.72 * g + 0.07 * b;
            *targetPixel = SDL_MapRGB(format, gray, gray, gray);
        }
    }
}