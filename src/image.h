/*!
 *  File created on 10/8/2020 (MM/DD/YYYY) by leo.duboin
 *  Contributors : leo.duboin
 *
 *  File containing all the necessary functions prototypes to interact with an image.
 *  It is the core of this project.
 * 
 *  10/20 : Modified version using the new image.c functions
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>

#define WHITE 255   // 8bit value for white
#define BLACK 0     // 8bit value for black

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
void extractImage(Image *image, const char *file, int height[2], int width[2]);

#endif
