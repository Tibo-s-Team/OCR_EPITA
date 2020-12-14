/*!
 *  File created on 12/12/2020 (MM/DD/YYYY) by florian.drevet
 *  Contributors : florian.drevet
 *
 *  Train NeuralNetwork to recognize images of characters
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "neuralnetwork.h"
#include "NN_functions.h"
#include "../image.h"
#include <math.h>
#include <dirent.h>
#include <string.h>
#include "OCR_NN.h"

/*!
 * Convert the most activated neuronne to the characters which is associated
 * @param neuralnetwork the neuralnetwork 
 * @return the characters that the neuralnetwork think it is
 */
char output_to_char(struct NeuralNetwork neuralnetwork)
{
    double *output = print_output(neuralnetwork);
    int neuronne_max = 0;
    double maxi_output = *output;
    for(int i = 0; i < (neuralnetwork.end-1)->nbr_neuronnes; i++)
    {
        if(*output > maxi_output)
        {
            neuronne_max = i;
            maxi_output = *output;
        }
        output += 1;
    }
    switch (neuronne_max)
    {
    case 0:
        return 'A';   
    case 1:
        return 'B';
    case 2:
        return 'C';
    case 3:
        return 'D';
    case 4:
        return 'E';
    case 5:
        return 'F';
    case 6:
        return 'G';
    case 7:
        return 'H';
    case 8:
        return 'I';
    case 9:
        return 'J';
    case 10:
        return 'K';
    case 11:
        return 'L';
    case 12:
        return 'M';
    case 13:
        return 'N';
    case 14:
        return 'O';
    case 15:
        return 'P';
    case 16:
        return 'Q';
    case 17:
        return 'R';
    case 18:
        return 'S';
    case 19:
        return 'T';
    case 20:
        return 'U';
    case 21:
        return 'V';
    case 22:
        return 'W';
    case 23:
        return 'X';
    case 24:
        return 'Y';
    case 25:
        return 'Z';
    case 26:
        return 'a';
    case 27:
        return 'b';
    case 28:
        return 'c';
    case 29:
        return 'd';
    case 30:
        return 'e';
    case 31:
        return 'f';
    case 32:
        return 'g';
    case 33:
        return 'h';
    case 34:
        return 'i';
    case 35:
        return 'j';
    case 36:
        return 'k';
    case 37:
        return 'l';
    case 38:
        return 'm';
    case 39:
        return 'n';
    case 40:
        return 'o';
    case 41:
        return 'p';
    case 42:
        return 'q';
    case 43:
        return 'r';
    case 44:
        return 's';
    case 45:
        return 't';
    case 46:
        return 'u';
    case 47:
        return 'v';
    case 48:
        return 'w';
    case 49:
        return 'x';
    case 50:
        return 'y';
    case 51:
        return 'z';
    default:
        return '$';
    }
}

/*!
 * Do one train of a neuralnetwork
 * @param neuralnetwork the neuralnetwork 
 * @param inputs inputs which is the pixels of the image
 * @param len_inputs number of elements in inputs
 * @param waited_outputs the values waited in output for the given inputs
 * @param coeff coeff for the updateweigth
 */
void one_training(NeuralNetwork neuralnetwork, 
                    double *inputs, 
                    int len_inputs, 
                    double waited_outputs[],
                    double coeff)
{
    feedForward(neuralnetwork, inputs, 625);
    backPropagation(neuralnetwork, waited_outputs);
    updateWeigth(neuralnetwork, inputs, len_inputs, coeff);
}

/*!
 * give the pointer to the beginning of a list of inputs for a neuralnetwork from an image
 * @param img image from which the inputs are created
 * @return pointer the list of inputs 
 * don't forget to free it
 */
double *inputs (Image* img)
{
    double *inputs = malloc(25 * 25 * sizeof(double));
    double *in = inputs;
    for (int i = 0; i < img->height; i++)
    {
        for (int j = 0; j < img->width; j++)
        {
            Uint8 r = 0;
            Uint8 g = 0;
            Uint8 b = 0;
            getPixelRGB(img, i, j, &r, &g, &b);
            double pixel_bi = (r+g+b)/(3*255);
            *in = pixel_bi;
            in += 1;
        }        
    }
    return inputs;
}

void character_training(double* inputs_neuronnes, NeuralNetwork neuralnetwork, Letter *letter, double waited[], double coeff)
{
    for (Image *l = letter->img; l < letter->img+letter->nbr_images; l++)
    {
        one_training(neuralnetwork, inputs_neuronnes, 625, waited, coeff);
    } 
}

void nbr_pictures(char* path, Letter *letter)
{
    int nbr = 0;
    struct dirent* ent = NULL;
    DIR* dir = opendir(path);
    while ((ent = readdir(dir)) != NULL)
    {
        if (strcmp(ent->d_name, ".") != 0 && 
            strcmp(ent->d_name, "..") != 0)
        nbr++;
    }

    letter->nbr_images = nbr;
}

void creat_list_img(Letter *letter)
{
    Image* list_img = malloc(letter->nbr_images * sizeof(Image));
    Image* l = list_img;
    struct dirent *lecture;
    DIR *rep;
    rep = opendir(letter->path);
    
    while ((lecture = readdir(rep))) {
        if (strcmp(lecture->d_name, ".") != 0 && strcmp(lecture->d_name, "..") != 0)
        {
            char *s3=NULL;
            s3=(char *)malloc((strlen(letter->path)+strlen(lecture->d_name))*sizeof(char));      
            strcpy(s3,letter->path);
            strcat(s3,lecture->d_name);
            *l = loadImage(s3);
            free(s3);
            l++;
        }
    }
    letter->img = list_img;
    closedir(rep);
}

Letter creat_letter(char* path)
{
    Letter letter;
    letter.path = path;
    nbr_pictures(path, &letter);
    creat_list_img(&letter);
    return letter;
}

void training_NN(NeuralNetwork neuralnetwork, Letter tab_letter[DONE], int len, double waited[NBR_LETTER][NBR_LETTER], int times, double coeff)
{
    double*** img_pixels = malloc(len * sizeof(double) * 625 * 20);
    double*** img_pixels_creation = img_pixels;
    for(int i = 0; i < len; i++)
    {
        int which_image = 0;
        double **images = malloc(sizeof(double) * 625 * 20);
        for (double** j = images; j < images + tab_letter[i].nbr_images; j++)
        {
            Image *img = tab_letter[i].img + which_image;
            double* inputs_neuronnes = inputs(img);
            *j = inputs_neuronnes;
            which_image += 1;
        }
        *img_pixels_creation = images;           
        img_pixels_creation += 1;
    }

    for(int t = 0; t < times; t++)
    {
        int which_letter = 0;
        for (double*** i = img_pixels; i < img_pixels+len; i++)
        {

            for (double** j = *i; j < *i + tab_letter[which_letter].nbr_images; j++)
            {   
                one_training(neuralnetwork, *j, 625, waited[which_letter], coeff);
            }
            which_letter+=1;
        }
        printf("%d\n", t);
    }

}

Image resize_images(Image img)
{
    if(img.height >25 && img.width > 25)
    {
        int decallage_x = (25-img.width)/2;
        int decallage_y = (25-img.height)/2;
        Image blanc = loadImage("/home/drevet/Documents/OCR_EPITA/src/NeuralNetwork_C/blanc.PNG");
        for(int i = 0; i < img.width; i++)
        {
            for(int j = 0; j < img.height; j++)
            {
                Uint8 r =0;
                Uint8 g = 0;
                Uint8 b = 0;
                getPixelRGB(&img, i, j, &r, &g, &b);
                Uint8 color[3] = {r, g, b}; 
                setPixelColor(&blanc, *color, decallage_x+i, decallage_y+j);
            }
        }
        return blanc;
    }
    return img;
}


