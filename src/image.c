#include "image.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------

void bitmap8(Image *image, Uint8 *pixels, const int pitch);

//-----------------------------------------------

// Loads an image from a file (PNG, JPG, BMP)
// Creates, initialize  and returns an Image struct
Image loadImage(const char *path) {
    SDL_Surface *surface = NULL;
    Image image;

    int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    int initted = IMG_Init(flags);
    if ((initted & flags) != flags) {
        printf(
            "ERROR: image.c - "
            "could not init required image format (jpg, png)\n");
        printf("%s", IMG_GetError());
    } else {
        surface = IMG_Load(path);
        if (surface == NULL)
            printf("ERROR: image.c - %s\n", IMG_GetError());
        else {
            SDL_LockSurface(surface);
            image.surface = surface;
            image.width = surface->w;
            image.height = surface->h;
            image.imageType = (surface->format->BytesPerPixel == 3) ? RGB : BW;
            image.bitmap = malloc(image.height * image.width * sizeof(Uint8));
        }
    }

    if (image.imageType == BW) bitmap8(&image, surface->pixels, surface->pitch);
    return image;
}

// Can be used to set a pixel's value
// Should not be used to modify an entire image's pixel value => inefficient
void setPixel(Image *image, const Uint8 color, const int x, const int y) {
    SDL_Surface *surface = image->surface;
    SDL_PixelFormat *format = surface->format;
    int width = image->width, height = image->height, pitch = surface->pitch;
    int bytes = format->BytesPerPixel;

    if (y >= height || x >= width) {
        printf(
            "ERROR: image.c : getPixel\n"
            "The given coordinates exceed the bitmpa size.");
        return;
    }

    Uint8 *ptr = &surface->pixels[y * pitch] + x * bytes;
    *ptr = (bytes == 1) ? color : SDL_MapRGB(format, color, color, color);
    image->bitmap[y * width + x] = color;
}

// get a pixel's color value from the bitmap according to coordinates
Uint8 getPixel(Image *image, const int x, const int y) {
    /*
        int width = image->width, height = image->height;

        if (y >= height || x >= width)
            printf(
                "ERROR: image.c : getPixel\n"
                "The given coordinates exceed the bitmpa size.");
    */
    // bitmap8(image, image->surface->pixels, image->surface->pixels);
    return image->bitmap[0];
}

// Fills the image's pixel bitmap when the pixels are coded on 8bits
void bitmap8(Image *image, Uint8 *pixels, const int pitch) {
    Uint8 *pixelPtr = NULL, *matrixPtr = NULL, *bitmap = image->bitmap;
    const int width = image->width, height = image->height;
    printf("test\n");

    bitmap = malloc(width * height * sizeof(Uint8));

    for (int y = 0; y < height; y++) {
        pixelPtr = &pixels[y * pitch];
        matrixPtr = &bitmap[y];
        for (int x = 0; x < width; x++, pixelPtr++, matrixPtr++) {
            *matrixPtr = *pixelPtr * 255;
        }
    }
}

// Displays an image in a external window
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
            if (e.type == SDL_QUIT || e.type == SDL_KEYUP) break;

        // refresh renderer
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, img, NULL, &texr);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(img);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
}