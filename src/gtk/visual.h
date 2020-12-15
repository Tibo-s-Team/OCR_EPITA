#ifndef IMAGE_H_
#define IMAGE_H_

#include <gtk/gtk.h>
#include <stdio.h> 
#include <string.h>
#include "../image.h"
#include "../preprocessing/preprocessing.h"
#include "../segmentation/segmentation.h"
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>

typedef struct {
    GtkWidget   *w_dlg_file_choose;       // Pointer to file chooser dialog box
    GtkWidget   *button1;   
    GtkWidget   *w_img_main;              // Pointer to image widget
    GtkWidget   *w_img_main1;
    GtkWidget   *label1;
} app_widgets;

void on_menuitm_open_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts);
void on_menuitm_close_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts);
void on_window_destroy();
void on_button1_clicked(GtkButton *b, app_widgets *app_wdgts);



#endif
