#ifndef IMG_H_
#define IMG_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef enum ImageType
{
    RGB,
    GRAYSCALED,
    BW
} ImageType;

typedef struct Image
{
    SDL_Surface *surface;
    int width, height;
    ImageType imageType;
    // color matrix
} Image;


Image loadImage(const char *path);
void displayImage(Image *image); 
void grayscaleImage(Image *image);
void grayscale32(Uint8 *pixels, SDL_PixelFormat *format, int width, int height, int pitch);

#endif