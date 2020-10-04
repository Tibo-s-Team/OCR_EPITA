#ifndef IMG_H_
#define IMG_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Surface *loadImage(char path[]);
void displayImage(SDL_Surface *image); 

#endif