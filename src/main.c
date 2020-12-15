/*!
 *  File created on 12/8/2020 (MM/DD/YYYY) by jean.barbaroux
 *  Contributors : jean.barbaroux
 *
 *  File containing the interface code. It means the work done in order to print
 * on the screnn our OCR's work
 */

//#include "visual.h"


/*!
 * This structure is used to create pointer
 * that will be used in the code to refer to
 * glade possibilities.
 */

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
    GtkWidget   *button1;  // button that activate the radio button to print the result
    GtkWidget *w_img_main;   // print on the left the file selected
    GtkWidget *w_img_main1;  // print on the right the result
    GtkWidget *OCR;          // radiobutton for OCR
    GtkWidget *greyscale;    // radio button for grayscale
    GtkWidget *bw;           // radiobutton for black and white
    GtkWidget *lseg;         // radiobutton for line segmentation
    GtkWidget *segment;      // radiobutton for segmentation
    GtkWidget *window;       // The window showed
    GtkWidget *savebutton;   // the save button
    GtkWidget *ocr;   // the save button
    GtkTextBuffer *textbuffer1;  
} app_widgets;


int main(int argc, char *argv[]) {
    app_widgets     *widgets = g_slice_new(app_widgets);
    GtkBuilder      *builder;
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("OCR_visual.glade");
    chdir("..");

    //Link glade and code together
    widgets->window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    widgets->w_dlg_file_choose = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_file_choose"));
    widgets->w_img_main = GTK_WIDGET(gtk_builder_get_object(builder, "img_main"));
    widgets->w_img_main1 = GTK_WIDGET(gtk_builder_get_object(builder, "img_main1"));
    widgets->button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    widgets->OCR = GTK_WIDGET(gtk_builder_get_object(builder, "OCR"));
    widgets->greyscale = GTK_WIDGET(gtk_builder_get_object(builder, "greyscale"));
    widgets->bw = GTK_WIDGET(gtk_builder_get_object(builder, "bw"));
    widgets->lseg = GTK_WIDGET(gtk_builder_get_object(builder, "lseg"));
    widgets->segment = GTK_WIDGET(gtk_builder_get_object(builder, "segment"));
    widgets->savebutton = GTK_WIDGET(gtk_builder_get_object(builder, "savebutton"));
    widgets->ocr = GTK_WIDGET(gtk_builder_get_object(builder, "ocr"));
    widgets->textbuffer1 = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "textbuffer1"));

    // put a background color --- Not really useful but nice
   GdkColor color;
    color.red = 0xa500;
    color.green = 0xa500;
    color.blue = 0xb500;
    gtk_widget_modify_bg(GTK_WIDGET(widgets->window), GTK_STATE_NORMAL, &color);
    gtk_builder_connect_signals(builder, widgets);
    g_object_unref(builder);
    gtk_widget_show(widgets->window);

    gtk_main();
    g_slice_free(app_widgets, widgets);
    return EXIT_SUCCESS;
}

/*!
 * Loads an image from a file and save it in a temporary directory.
 * @param path the path to the image to save
 *  (can be absolute or relative to the workspace folder)
 * @return nothing, but Pictures are saved
 */

void SaveImage(char *path) {
    Image image;
    Image tmp;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_GETEVENT) < 0) {
        printf("Error: failed to initialize SDL: %s", SDL_GetError());
    } else {
        image = loadImage(path);
        grayscale(&image);
        SDL_SaveBMP(image.surface, "tests/images/gtk/grayscaled");
        Bradley(&image);
        SDL_SaveBMP(image.surface, "tests/images/gtk/blackandwhited");
        FILE *f = fopen("tests/images/gtk/output.txt","w");
        if (f == NULL)
        {
            printf("Error opening file!\n");
            exit(1);
        }
        //fprintf(f, "test\n");
        bin_segmentation(&image, f);
        fclose(f);
    }
}

/*!
 * Loads an image from a file and returns an Image struct.
 * @param menuitem
 * @param app_wdgts refers to the structure in order to use the Glade
 * possibilities (can be absolute or relative to the workspace folder)
 * @return nothing, but open the picture in the interface.
 */
void on_menuitm_open_activate(GtkMenuItem *m, app_widgets *app_wdgts)
{
    char *file_name = NULL;
    gtk_widget_show(app_wdgts->w_dlg_file_choose);
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->w_dlg_file_choose)) == GTK_RESPONSE_OK) {
        file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->w_dlg_file_choose));
        if (file_name != NULL) {
            gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), file_name);
            gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main1), file_name);
            SaveImage(file_name);
        }
        g_free(file_name);
    }
    gtk_widget_hide(app_wdgts->w_dlg_file_choose);
}


/*!
 * close the menu
 * @param menuitem
 * @param app_wdgts refers to the structure in order to use the Glade
 * possibilities (can be absolute or relative to the workspace folder)
 * @return nothing
 */

void on_menuitm_close_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts) {
    gtk_main_quit();
}

void on_window_destroy() { gtk_main_quit(); }

/*!
 * Loads the expected result from the radio button to theright of the screen
 * @param b
 * @param app_wdgts refers to the structure in order to use the Glade
 * possibilities
 * @return nothing
 */
void on_button1_clicked(GtkButton *b, app_widgets *app_wdgts) {
    gboolean T =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->greyscale));
    if (T) {
        gchar *filename = "tests/images/gtk/grayscaled";
        gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main1), filename);
    }
    T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->bw));
    if (T) {
        gchar *filename = "tests/images/gtk/blackandwhited";
        gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main1), filename);
    }
    T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->lseg));
    if (T) {
        gchar *filename = "tests/images/gtk/linesegmentated";
        gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main1), filename);
    }
    T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->segment));
    if (T) {
        gchar *filename = "tests/images//gtk/segmentated";
        gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main1), filename);
    }
    T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->OCR));
    if (T) {
    gboolean file_success = 0;
    gchar *filename =  "tests/images/gtk/output.txt";        // Name of file to open from dialog box
    gchar *file_contents = NULL;    // For reading contents of file
     if (file_success = g_file_get_contents(filename, &file_contents, NULL, NULL)){
        gtk_text_buffer_set_text(app_wdgts->textbuffer1, file_contents, -1);
     }
     g_free(file_contents);
    }
}

/*!
 * When the button is clicked, it opens a file managerto save the right image
 * @param sv
 * @param app_wdgts refers to the structure in order to use the Glade
 * possibilities
 * @return nothing
 */

void on_savebutton_clicked(GtkButton *sv, app_widgets *app_wdgts) {
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new(
        "Save File", NULL, GTK_FILE_CHOOSER_ACTION_SAVE, GTK_STOCK_CANCEL,
        GTK_RESPONSE_CANCEL, GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT, NULL);
    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog),
                                                   TRUE);

    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), "../Images");
    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog),
                                      "Untitled document");

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename;
        Image image;
        char *path;
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        gboolean T = gtk_toggle_button_get_active(
            GTK_TOGGLE_BUTTON(app_wdgts->greyscale));
        if (T) {
            path = "tests/images/gtk/grayscaled";
            Image image = loadImage(path);
            SDL_SaveBMP(image.surface, filename);
        }
        T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->bw));
        if (T) {
            path = "tests/images/gtk/blackandwhited";
            Image image = loadImage(path);
            SDL_SaveBMP(image.surface, filename);
        }
        T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->lseg));
        if (T) {
            path = "tests/images/gtk/linesegmentated";
            Image image = loadImage(path);
            SDL_SaveBMP(image.surface, filename);
        }
        T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->segment));
        if (T) {
            path = "tests/images/gtk/segmentated";
            Image image = loadImage(path);
            SDL_SaveBMP(image.surface, filename);
        }
        T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_wdgts->OCR));
        if (T) {
            path = "tests/images/gtk/grayscaled";
        image = loadImage(path);
        image.imageType = GRAYSCALE;
        FILE *f = fopen(filename,"w");
        if (f == NULL)
        {
            
            printf("Error opening file!\n");
            exit(1);
        }
        //fprintf(f, "test\n")
        Bradley(&image);
        filterImage(&image,SHARPNESS);
        blackAndWhite(&image);
        bin_segmentation(&image, f);
        fclose(f);
    }
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}