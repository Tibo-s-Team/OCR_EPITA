#ifndef VISUAL_H_
#define VISUAL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Image/image.h"
#include "preprocessing/preprocessing.h"
#include "segmentation/segmentation.h"

typedef struct {
    GtkWidget *w_dlg_file_choose;  // FileChooser
    GtkWidget
        *button1;  // button that activate the radio button to print the result
    GtkWidget *w_img_main;   // print on the left the file selected
    GtkWidget *w_img_main1;  // print on the right the result
    GtkWidget *OCR;          // radiobutton for OCR
    GtkWidget *greyscale;    // radio button for grayscale
    GtkWidget *bw;           // radiobutton for black and white
    GtkWidget *lseg;         // radiobutton for line segmentation
    GtkWidget *segment;      // radiobutton for segmentation
    GtkWidget *window;       // The window showed
    GtkWidget *savebutton;   // the save button
} app_widgets;

int mainGTK(int argc, char *argv[]);

void on_menuitm_open_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts);
void on_menuitm_close_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts);
void on_window_destroy();
void on_button1_clicked(GtkButton *b, app_widgets *app_wdgts);

#endif
