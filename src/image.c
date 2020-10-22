#include "image.h"

// Loads an image from a file and returns an Image struct
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
        }
    }

    return image;
}

#pragma region getPixel

// Returns the address in memory of the pixel at the (x, y) coordinate
static inline Uint8 *getPixelRef(SDL_Surface *surf, int x, int y) {
    if (x > surf->w || y > surf->h)
        errx(1, "Error: image.c - getPixelRef : IndexOutOfBounds.");

    Uint8 bpp = surf->format->BytesPerPixel;
    return (Uint8 *)surf->pixels + y * surf->pitch + x * bpp;
}

/*!
 * Stores the rgb value of the pixel at the (x, y) coordinate.
 * @param image a non BW image (bits stored on 3 or 4 bytes)
 * @param r red value output
 * @param g green value output
 * @param b blue value output
 */
void getPixelRGB(Image *image, const int x, const int y, Uint8 *r, Uint8 *g,
                 Uint8 *b) {
    Uint8 *pixel = getPixelRef(image->surface, x, y);
    Uint32 color;

    if (image->imageType == BW) {
        warnx(
            "Warning: image.c - getPixelRGB : image's pixels must be encoded "
            "on 32B of data. "
            "Skipped.");
        return;
    }

    // Bitwise operation to create a RGB representation of the pixel's color
    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        color = pixel[0] << 16 | pixel[1] << 8 | pixel[2];
    else
        color = pixel[0] | pixel[1] << 8 | pixel[2] << 16;

    SDL_GetRGB(color, image->surface->format, r, g, b);
}

/*!
 * @return 8bits color value of a pixel
 * @param image greyscaled / BW image (same R G & B for each pixel)
 */
Uint8 getPixelColor(Image *image, const int x, const int y) {
    Uint8 *pixel = getPixelRef(image->surface, x, y);
    Uint8 r, g, b;

    switch (image->imageType) {
        case RGB:
            warnx(
                "Warning: image.c - getPixelColor : imageType must not be "
                "RGB. "
                "Skipped.");
            return 0;
        case GRAYSCALE:
            getPixelRGB(image, x, y, &r, &g, &b);
            return g;
        case BW:
            // SDL - 8bits : 0 = white & 1 = black
            return !(*pixel) * 255;
    }

    return 0;
}

#pragma endregion getPixel

/*!
 * Changes the color of a pixel to a shade of grey.
 * @param color new color will be of the form RGB(color, color, color).
 * If image is BW anything other than black will result in a white pixel.
 */
void setPixelColor(Image *image, Uint8 color, const int x, const int y) {
    Uint8 *pixel = getPixelRef(image->surface, x, y);

    if (image->imageType == BW)
        *pixel = color == 0;
    else {
        pixel[0] = color;
        pixel[1] = color;
        pixel[2] = color;
    }
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
