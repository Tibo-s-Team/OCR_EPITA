#include <gtk/gtk.h>
#include <stdio.h> 
#include <string.h> 
#include <SDL/SDL.h>
#include "../src/preprocessing/preprocessing.h"
#include "../src/preprocessing/suppression_couleurs.c"
#include "../src/image.h"
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
    gchar *filename;
} app_widgets;

int main(int argc, char *argv[])
{
    GtkBuilder      *builder;
    GtkWidget       *window;
    app_widgets     *widgets = g_slice_new(app_widgets);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("OCR_visual.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    widgets->w_dlg_file_choose = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_file_choose"));
    widgets->w_img_main = GTK_WIDGET(gtk_builder_get_object(builder, "img_main"));
    widgets->w_img_main1 = GTK_WIDGET(gtk_builder_get_object(builder, "img_main1"));
    widgets->button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    widgets->label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
    
    gtk_builder_connect_signals(builder, widgets);
    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();
    g_slice_free(app_widgets, widgets);
    

	return EXIT_SUCCESS;
}

// File --> Open
void on_menuitm_open_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gchar *file_name = NULL;        // Name of file to open from dialog box
    
    // Show the "Open Image" dialog box
    gtk_widget_show(app_wdgts->w_dlg_file_choose);
    
    // Check return value from Open Image dialog box to see if user clicked the Open button
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->w_dlg_file_choose)) == GTK_RESPONSE_OK) {
        // Get the file name from the dialog box
        file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->w_dlg_file_choose));
        if (file_name != NULL) {
            gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), file_name);
        }
        g_print("%s", file_name);
        g_free(file_name);
        app_wdgts->filename = file_name;
    }

    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(app_wdgts->w_dlg_file_choose);
}

// File --> Quit
void on_menuitm_close_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gtk_main_quit();
}

// called when window is closed
void on_window_destroy()
{
    gtk_main_quit();
}


void on_button1_clicked(GtkButton *b, app_widgets *app_wdgts){
      //  char *filename = "/home/jbbx/Pictures/emoji.png";
}