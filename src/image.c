#include "image.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char Uint8;
typedef unsigned int Uint32;

Image loadImage(const char *path) 
{
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
            image.bitmap = NULL;
        }
    }

    return image;
}

void displayImage(Image *image) 
{
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
            if (e.type == SDL_QUIT || e.type == SDL_KEYUP)
                break;

        // refresh renderer
        SDL_RenderClear(renderer);                   
        SDL_RenderCopy(renderer, img, NULL, &texr);  
        SDL_RenderPresent(renderer);                 
    }

    SDL_DestroyTexture(img);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
}

void grayscale32(Uint8 *pixels, SDL_PixelFormat *format, int *seuil,
    int width, int height, int pitch);

void grayscaleImage(Image *image)
{
    SDL_Surface *surface = image->surface;
    Uint8 *pixels = surface->pixels;

    if(surface->format->BytesPerPixel == 1 && image->imageType == RGB)
        image->imageType = GRAYSCALED; // image en niveaux de gris d'origine 
    if (image->imageType != RGB) return;

    int locked = SDL_MUSTLOCK(surface);
    if (!locked) SDL_LockSurface(surface);

    grayscale32(pixels, surface->format, &image->seuil, 
        image->width, image->height,surface->pitch);
    image->imageType = GRAYSCALED;

    if (!locked) SDL_UnlockSurface(surface);
}

void grayscale32(Uint8 *pixels, SDL_PixelFormat *format, int *seuil,
    int width, int height, int pitch)
{
    Uint8 *byteptr = NULL;
    Uint32 *targetPixel = NULL;
    Uint8 r, g, b, gray;

    // pixels : height * rows of (3 * width) pixels
    // a pixel stores info on 3 bytes
    for (int y = 0; y < height; y++) {
        byteptr = &pixels[y * pitch];
        for (int x = 0; x < width; x++, byteptr += 3) {
            targetPixel = (Uint32 *) byteptr;
            SDL_GetRGB(*targetPixel, format, &r, &g, &b);

            gray = 0.21 * r + 0.72 * g + 0.07 * b; // grayscaling formula
            *seuil += gray;
            *targetPixel = SDL_MapRGB(format, gray, gray, gray);
        }
    }

    *seuil /= width * height; // average value of all grayscaled pixels
}


void bw32(Uint8 *pixels, SDL_PixelFormat *format, int seuil,
    int width, int height, int pitch);

void blackAndWhite(Image *image)
{
    SDL_Surface *surface = image->surface;
    SDL_PixelFormat *format = surface->format;
    
    if(image->imageType != GRAYSCALED)
        return;

    if(format->BytesPerPixel != 3)
        printf("ERROR: image.c: blackAndWhite -\nPixelFormat not supported (must be 8 or 32 bits).\n");
    else{
        bw32(surface->pixels, format, image->seuil, 
            image->width, image->height, surface->pitch);
        image->imageType = BW;
    }
}

//TODO: fill pixel matrice
void bw32(Uint8 *pixels, SDL_PixelFormat *format, int seuil,
    int width, int height, int pitch)
{
    Uint8 *byteptr = NULL;
    Uint32 *targetPixel = NULL;
    Uint8 r, g, b, bw;

    for (int y = 0; y < height; y++){
        byteptr = &pixels[y * pitch];
        for(int x = 0; x < width; x++, byteptr += 3){
            targetPixel = (Uint32 *) byteptr;
            SDL_GetRGB(*targetPixel, format, &r, &g, &b);
            bw = (g < seuil) ? 0 : 255;
            *targetPixel = SDL_MapRGB(format, bw, bw, bw);
        }
    }
}