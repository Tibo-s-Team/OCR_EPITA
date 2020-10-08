#include "image.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------

void grayscale32(Image *image, Uint8 *pixels, SDL_PixelFormat *format,
                 const int pitch);

void bw32(Image *image, Uint8 *pixels, SDL_PixelFormat *format,
                 const int pitch);

void bitmap8(Image *image, Uint8 *pixels,
                 const int pitch);

//-----------------------------------------------

Image loadImage(const char *path) {
    SDL_Surface *surface = NULL;
    Image image;

    int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    int initted = IMG_Init(flags);
    if ((initted & flags) != flags) {
        printf(
            "ERROR: image_loading.c - "
            "could not init required image format (jpg, png)\n");
        printf("%s", IMG_GetError());
    } else {
        surface = IMG_Load(path);
        if (surface == NULL)
            printf("ERROR: image_loading.c - %s\n", IMG_GetError());
        else {
            image.surface = surface;
            image.width = surface->w;
            image.height = surface->h;
            // Image can be either RGB or B&W on load
            image.imageType = (surface->format->BytesPerPixel == 3) ? RGB : BW;
            image.bitmap = NULL;
        }
    }

    if (image.imageType == BW)
        bitmap8(&image, surface->pixels, surface->pitch);
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

void grayscaleImage(Image *image) {
    SDL_Surface *surface = image->surface;
    Uint8 *pixels = surface->pixels;

    if (surface->format->BytesPerPixel == 1 && image->imageType == RGB)
        image->imageType = GRAYSCALED;  // image en niveaux de gris d'origine
    if (image->imageType != RGB) return;

    int locked = SDL_MUSTLOCK(surface);
    if (!locked) SDL_LockSurface(surface);

    grayscale32(image, pixels, surface->format, surface->pitch);
    image->imageType = GRAYSCALED;

    if (!locked) SDL_UnlockSurface(surface);
}

void grayscale32(Image *image, Uint8 *pixels, SDL_PixelFormat *format,
                 const int pitch) {
    Uint8 *byteptr = NULL, *matrixPtr = NULL, *bitmap = image->bitmap;
    Uint32 *targetPixel = NULL;
    Uint8 r, g, b, gray;
    int width = image->width, height = image->height;

    bitmap = malloc(height * width * sizeof(Uint8));

    // pixels : height * rows of (3 * width) pixels
    // a pixel stores info on 3 bytes
    for (int y = 0; y < height; y++) {
        byteptr = &pixels[y * pitch];
        matrixPtr = &bitmap[y];
        for (int x = 0; x < width; x++, matrixPtr++, byteptr += 3) {
            targetPixel = (Uint32 *)byteptr;
            SDL_GetRGB(*targetPixel, format, &r, &g, &b);

            gray = 0.21 * r + 0.72 * g + 0.07 * b;  // grayscaling formula
            image->seuil += gray;
            *targetPixel = SDL_MapRGB(format, gray, gray, gray);

            *matrixPtr =  gray;
        }
    }

    image->seuil /= width * height;  // average value of all grayscaled pixels
}

void blackAndWhite(Image *image) {
    SDL_Surface *surface = image->surface;
    SDL_PixelFormat *format = surface->format;

    if (image->imageType !=
        GRAYSCALED)  // Can only apply to a Grayscaled 32bits image
        return;

    if (format->BytesPerPixel != 3) {
        printf("ERROR: image.c: blackAndWhite -\n");
        printf("PixelFormat not supported (must be 8 or 32 bits).\n");
    } else {
        bw32(image, image->surface->pixels, format, surface->pitch);
        image->imageType = BW;
    }
}

void bw32(Image *image, Uint8 *pixels, SDL_PixelFormat *format,
                 const int pitch) {
    Uint8 *byteptr = NULL, *matrixPtr = NULL, *bitmap = image->bitmap;
    Uint32 *targetPixel = NULL;
    Uint8 r, g, b, bw;
    int width = image->width, height = image->height;

    bitmap = malloc(width * height * sizeof(Uint8));

    for (int y = 0; y < height; y++) {
        byteptr = &pixels[y * pitch];
        matrixPtr = &bitmap[y];
        for (int x = 0; x < width; x++, byteptr += 3, matrixPtr++) {
            targetPixel = (Uint32 *)byteptr;
            SDL_GetRGB(*targetPixel, format, &r, &g, &b);
            bw = (g < image->seuil) ? 0 : 255;
            *matrixPtr = (Uint8)(bw / 255);
            *targetPixel = SDL_MapRGB(format, bw, bw, bw);
        }
    }
}

// Fills the image's pixel bitmap when the pixels are coded on 8bits
void bitmap8(Image *image, Uint8 *pixels,
                 const int pitch) {
    Uint8 *pixelPtr = NULL, *matrixPtr = NULL, *bitmap = image->bitmap;
    const int width = image->width, height = image->height;
    bitmap = malloc(width * height * sizeof(Uint8));

    for (int y = 0; y < height; y++) {
        pixelPtr = &pixels[y * pitch];
        matrixPtr = &bitmap[y];
        for (int x = 0; x < width; x++, pixelPtr++, matrixPtr++) {
            *matrixPtr = *pixelPtr;
        }
    }
}