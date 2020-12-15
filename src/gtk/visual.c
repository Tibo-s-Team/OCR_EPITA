#include <gtk/gtk.h>
#include <stdio.h> 
#include <string.h>
#include "../image.h"
#include "../preprocessing/preprocessing.h"
#include "../segmentation/segmentation.h"
#include "visual.h"
#include <stdlib.h>
/*#include <SDL/SDL.h>
#include <SDL/SDL_image.h>*/
#include <err.h>

typedef struct {
    GtkWidget   *w_dlg_file_choose;       // Pointer to file chooser dialog box
    GtkWidget   *button1;   
    GtkWidget   *w_img_main;              // Pointer to image widget
    GtkWidget   *w_img_main1;
    GtkWidget   *label1;
    GtkWidget   *sav;
    GtkWidget   *OCR;
    GtkWidget   *greyscale;
    GtkWidget   *bw;
    GtkWidget   *lseg;
    GtkWidget   *segment;
    GtkWidget   *window;
    GtkWidget   *save;
    GtkWidget   *file1;
    GtkWidget   *entry1;
    GtkWidget   *savebutton;
} app_widgets;


int main(int argc, char *argv[])
{
    app_widgets     *widgets = g_slice_new(app_widgets);
    GtkBuilder      *builder;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("OCR_visual.glade");

    widgets->window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    widgets->w_dlg_file_choose = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_file_choose"));
    widgets->w_img_main = GTK_WIDGET(gtk_builder_get_object(builder, "img_main"));
    widgets->w_img_main1 = GTK_WIDGET(gtk_builder_get_object(builder, "img_main1"));
    widgets->button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    widgets->label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
    widgets->OCR = GTK_WIDGET(gtk_builder_get_object(builder, "OCR"));
    widgets->greyscale = GTK_WIDGET(gtk_builder_get_object(builder, "greyscale"));
    widgets->bw = GTK_WIDGET(gtk_builder_get_object(builder, "bw"));
    widgets->lseg = GTK_WIDGET(gtk_builder_get_object(builder, "lseg"));
    widgets->segment = GTK_WIDGET(gtk_builder_get_object(builder, "segment"));
    widgets->sav = GTK_WIDGET(gtk_builder_get_object(builder, "sav"));
    widgets->save = GTK_WIDGET(gtk_builder_get_object(builder, "save"));
    widgets->file1 = GTK_WIDGET(gtk_builder_get_object(builder, "file1"));
    widgets->entry1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry1"));
    widgets->savebutton = GTK_WIDGET(gtk_builder_get_object(builder, "savebutton"));

        GdkColor color; // default background color
        color.red = 0xa500;
        color.green = 0xa500;
        color.blue = 0xb500;
        gtk_widget_modify_bg(GTK_WIDGET(widgets->window), GTK_STATE_NORMAL, &color);

        color.red = 0x0000;
        color.green = 0x0000;
        color.blue = 0x0000;
    
    gtk_builder_connect_signals(builder, widgets);
    g_object_unref(builder);

    gtk_widget_show(widgets->window);                
    gtk_main();
    g_slice_free(app_widgets, widgets);
    

	return EXIT_SUCCESS;
}


void SaveImage(char *path){
    Image image;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_NUMEVENTS) < 0) {
        printf("Error: failed to initialize SDL: %s", SDL_GetError());
        }
         else {
                Image image = loadImage(path);
                     grayscale(&image);
                         SDL_SaveBMP(image.surface, "../../tests/tmp/grayscaled");
                     blackAndWhite(&image);
                         SDL_SaveBMP(image.surface, "../../tests/tmp/blackandwhited");
                    lineSegmentation(&image);
                          SDL_SaveBMP(image.surface, "../../tests/tmp/linesegmentated");
                    segmentation(&image);
                        SDL_SaveBMP(image.surface, "../../tests/tmp/segmentated");
                }
            
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
            gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main1), file_name);
            SaveImage(file_name);
        }
        g_free(file_name);
    }
    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(app_wdgts->w_dlg_file_choose);
}

void on_save_clicked(GtkMenuItem *m, app_widgets *app_wdgts)
{
   gchar *file_name = NULL;        // Name of file to open from dialog box
    
    // Show the "Open Image" dialog box
    gtk_widget_show(app_wdgts->sav);
    
    // Check return value from Open Image dialog box to see if user clicked the Open button
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->sav)) == GTK_RESPONSE_OK) {
        // Get the file name from the dialog box
        file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->sav));
        if (file_name != NULL) {
            gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), file_name);
            gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main1), file_name);
            SaveImage(file_name);
        }
        g_free(file_name);
    }
    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(app_wdgts->sav);
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
    
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->greyscale));
	if (T){ gchar *filename = "../../tests/tmp/grayscaled"; 
        gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main1), filename);
    }
    T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->bw));
	if (T){ gchar *filename = "../../tests/tmp/blackandwhited"; 
        gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main1), filename);
    }
     T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->lseg));
	if (T){ gchar *filename = "../../tests/tmp/linesegmentated"; 
        gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main1), filename);
    }
    T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->segment));
	if (T){ gchar *filename = "../../tests/tmp/segmentated"; 
        gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main1), filename);
    }
    T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->OCR));
	if (T){ gchar *filename = "../../tests/tmp/grayscaled"; 
        gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main1), filename);
    }
}

void on_savebutton_clicked(GtkButton *sv, app_widgets *app_wdgts ){ 
    GtkWidget *dialog;
     dialog = gtk_file_chooser_dialog_new ("Save File",
     				      NULL,
     				      GTK_FILE_CHOOSER_ACTION_SAVE,
     				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
     				      GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
     				      NULL);
     gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (dialog), TRUE);
     
         gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (dialog), "../../tests");
         gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (dialog), "Untitled document");
     
     if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
       {
         char *filename;
            Image image;
            char *path;
         filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
          g_print("%s\n",filename);
	        gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->greyscale));
	        if (T){ path = "../../tests/tmp/grayscaled"; 
                Image image = loadImage(path);
                SDL_SaveBMP(image.surface, filename);
            }
            T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->bw));
	        if (T){path = "../../tests/tmp/blackandwhited";
                Image image = loadImage(path);
                SDL_SaveBMP(image.surface, filename); 
            }
            T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->lseg));
        	if (T){path = "../../tests/tmp/linesegmentated"; 
                Image image = loadImage(path);
                SDL_SaveBMP(image.surface, filename);
            }
            T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->segment));
	        if (T){path = "../../tests/tmp/segmentated"; 
                Image image = loadImage(path);
                SDL_SaveBMP(image.surface, filename);
            }
            T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->OCR));
	        if (T){path = "../../tests/tmp/grayscaled";
                Image image = loadImage(path);
                SDL_SaveBMP(image.surface, filename);
            }
         g_free (filename);
       }
     
     gtk_widget_destroy (dialog);
}
















           