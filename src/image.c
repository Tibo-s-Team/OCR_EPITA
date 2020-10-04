#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Surface *loadImage(const char *path)
{
    SDL_Surface *image = NULL;

    int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    int initted = IMG_Init(flags);
    if( (initted & flags) != flags ) {
       printf("ERROR: image_loading.c - could not init required image format (jpg, png)\n");
       printf("%s", IMG_GetError()); 
    }
    else {
        image = IMG_Load(path);
        if(image == NULL)
            printf("ERROR: image_loading.c - %s\n", IMG_GetError());
    }

    return image;
}

void displayImage(SDL_Surface *image)
{
    const int WIDTH = (*image).w, HEIGHT = (*image).h;

    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *img = NULL;

    // create rendering context
    win = SDL_CreateWindow("Image Preview", 100, 100, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    // load image
    img = SDL_CreateTextureFromSurface(renderer, image);
	SDL_Rect texr; 
    texr.x = 0; texr.y = 0; // placed in the top left corner of or window 
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