#ifndef IMAGE_H_
#define IMAGE_H_

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>

#define WHITE 255
#define BLACK 0

typedef enum ImageType { RGB, GRAYSCALE, BW } ImageType;

typedef struct Image {
    SDL_Surface *surface;
    int width, height;
    ImageType imageType;
} Image;

Image loadImage(const char *path);
Uint8 getPixelColor(Image *image, const int x, const int y);
void getPixelRGB(Image *image, const int x, const int y, 
                Uint8 *r, Uint8 *g, Uint8 *b);
void setPixelColor(Image *image, Uint8 color, 
                const int x, const int y);
void displayImage(Image *image);

#endif