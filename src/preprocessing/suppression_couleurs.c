#include <stdio.h>
#include <stdlib.h>

#include "../image.h"

//-----------------------------------------------

void grayscale32(Image *image, Uint8 *pixels, SDL_PixelFormat *format,
                 const int pitch);

void bw32(Image *image, Uint8 *pixels, SDL_PixelFormat *format,
          const int pitch);

//-----------------------------------------------

#pragma region grayscale

// Applies a grayscaling algorithm onto the image
// Fills its structure's bitmap afterwards
void grayscaleImage(Image *image) {
    SDL_Surface *surface = image->surface;
    Uint8 *pixels = surface->pixels;

    if (surface->format->BytesPerPixel == 1 && image->imageType == RGB)
        image->imageType = GRAYSCALED;  // image en niveaux de gris d'origine
    if (image->imageType != RGB) return;

    grayscale32(image, pixels, surface->format, surface->pitch);
    image->imageType = GRAYSCALED;
}

// Grayscaling algorithm for an image coded on 32bits and bitmap filling
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

            *matrixPtr = gray;
        }
    }

    image->seuil /= width * height;  // average value of all grayscaled pixels
}

#pragma endregion grayscale

#pragma region black_and_white

// Applies black and white algorithm onto an image and updates its bitmap
// @param image : greyscaled image (uniformed RGB values for each pixel)
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

// Applies black and white algorithm onto image encoded on 32bits
// Fills its bitmap afterwards
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
            *matrixPtr = (Uint8)bw;
            *targetPixel = SDL_MapRGB(format, bw, bw, bw);
        }
    }
}

#pragma endregion black_and_white