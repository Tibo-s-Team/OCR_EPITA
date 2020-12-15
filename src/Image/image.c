/*!
 *  File created on 10/8/2020 (MM/DD/YYYY) by leo.duboin
 *  Contributors : leo.duboin
 *
 *  File containing all the functions necessary to interact with an image.
 *
 *  10/20 : Cleaned code by mixing it with some functions seen in class
 *  12/10 : Added saveImage => memory leak issue
 *  12/12 : Added imageRotation
 */

#include "image.h"

/*!
 * Loads an image from a file and returns an Image struct.
 * @param path the path to the image to load
 *  (can be absolute or relative to the workspace folder)
 * @return an image structure with all the loaded image's information
 */
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

/*!
 * Returns the address in memory of the pixel at the (x, y) coordinate.
 * @param surf the surface to get the pixel's information from
 * @return a pointer to the pixel's memory address
 */
static inline Uint8 *getPixelRef(SDL_Surface *surf, int x, int y) {
    if (x > surf->w || y > surf->h)
        errx(1,
             "Error: image.c - getPixelRef : IndexOutOfBounds (%d,%d) and "
             "image is %dx%d",
             x, y, surf->w, surf->h);

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

    if (image->surface->format->BytesPerPixel <= 2) {
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
 * Returns the pixel color of a nn RGB image.
 * @param image greyscaled / BW image (same R G & B for each pixel)
 * @return 8bits color value of a pixel
 */
Uint8 getPixelColor(Image *image, const int x, const int y) {
    Uint8 *pixel = getPixelRef(image->surface, x, y);
    Uint8 r, g, b;

    if (image->imageType == RGB) {
        warnx(
            "Warning: image.c - getPixelColor : imageType must not be "
            "RGB. Use getPixelColorRGB() instead."
            "Skipped.");
        return 0;
    }

    if (image->surface->format->BytesPerPixel <= 2)
        // SDL - 8bits : 0 = white & 1 = black
        return !(*pixel) * 255;

    getPixelRGB(image, x, y, &r, &g, &b);
    return g;
}

#pragma endregion getPixel

/*!
 * Change the color of a pixel to a shade of grey.
 * @param color new color will be of the form RGB(color, color, color).
 *  If image is BW anything other than black will result in a white pixel.
 */
void setPixelColor(Image *image, Uint8 color, const int x, const int y) {
    Uint8 *pixel = getPixelRef(image->surface, x, y);

    if (image->surface->format->BytesPerPixel == 1)
        *pixel = color == 0;
    else {
        pixel[0] = color;
        pixel[1] = color;
        pixel[2] = color;
    }
}

/*!
 * Display an image in an external window.
 *  Image will not be resized nor modified.
 * @param image the image to display on screen
 */
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

/*!
 * Extract part of an image and save it as a new image.
 * @param image the image to extract from
 * @param file the file where to save the new image
 * @param height tuple contating the starting and ending height
 *  of the part of the image to extract
 * @param width tuple contating the starting and ending width
 *  of the part of the image to extract
 */
void extractImage(Image *image, const char *file, BBox area) {
    SDL_Rect rect = {.x = area.start.x,
                     .y = area.start.y,
                     .w = area.end.x - area.start.x,
                     .h = area.end.y - area.start.y};
    SDL_Surface *cropped =
        SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0);

    // create new blank surface
    // verify path doesn't already exist
    SDL_UnlockSurface(image->surface);

    // extract image part => returns 0 if succesful
    int extraction = SDL_BlitSurface(image->surface, &rect, cropped, NULL);
    if (extraction)
        errx(1,
             "Error : image.c - extractImage : Image couldn't be extracted.");

    SDL_SaveBMP(cropped, file);
    SDL_FreeSurface(cropped);
    IMG_Quit();
}

/*!
 * rotates the image according to an angle
 * @param angle the angle we want to rotate the image with
 * @param matrix the matrix of the image
 * @param w the width of the matrix
 * @param h the height of the matrix
 */
void imageRotation(Image *image, double angle) {
    return;

    // FIXME

    int w = image->width, h = image->height;
    Uint8 bpp = image->surface->format->BytesPerPixel;
    double ray = sqrt(w * w + h * h);

    // save old pixels information
    Uint8 *rotated = calloc(h * image->surface->pitch, sizeof(Uint8));

    for (double i = 0; i < w; i++) {
        for (double j = 0; j < h; j++) {
            // new coordinates of the current pixel
            int y = (int)(i * cos(angle) + j * sin(angle));
            int x = (int)((-1) * i * sin(angle) + j * cos(angle));

            // get old pixel values
            Uint8 r, g, b;
            if (image->imageType == RGB)
                getPixelRGB(image, i, j, &r, &g, &b);
            else {
                r = getPixelColor(image, i, j);
                g = r;
                b = r;
            }
            if (x > w || x < 0 || y < 0 || y > h) printf("test\n");
        }
    }

    memcpy(image->surface->pixels, rotated, image->surface->pitch * h);
    free(rotated);
}
