#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "image.h"

Image loadImage(const char *path)
{
    SDL_Surface *surface = NULL;
    Image image;

    int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    int initted = IMG_Init(flags);
    if( (initted & flags) != flags ) {
       printf("ERROR: image_loading.c - could not init required image format (jpg, png)\n");
       printf("%s", IMG_GetError()); 
    }
    else {
        surface = IMG_Load(path);
        if(surface == NULL)
            printf("ERROR: image_loading.c - %s\n", IMG_GetError());
        else{
            image.surface = surface;
            image.width = (*surface).w; image.height = (*surface).h;
            image.imageType = RGB;
        }
    }

    return image;
}

void displayImage(Image *image)
{
    const int WIDTH = (*image).width, HEIGHT = (*image).height;

    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *img = NULL;

    // create rendering context
    win = SDL_CreateWindow("Image Preview", 100, 100, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    // load image
    img = SDL_CreateTextureFromSurface(renderer, (*image).surface);
	SDL_Rect texr; 
    texr.x = 0; texr.y = 0; // placed in the top left corner of the window 
    texr.w = WIDTH; texr.h = HEIGHT; // set to the size of the window

	
	while(1) {
		
		SDL_Event e;
		if ( SDL_PollEvent(&e) ) 
			if (e.type == SDL_QUIT) // escape key
				break;
		
		// refresh renderer
		SDL_RenderClear(renderer); // clear the screen
		SDL_RenderCopy(renderer, img, NULL, &texr); // save renderer
		SDL_RenderPresent(renderer); // update renderer
		
	}
	
	SDL_DestroyTexture(img);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
}