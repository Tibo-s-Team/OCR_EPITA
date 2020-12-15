/*!
 *  File created on 12/12/2020 (MM/DD/YYYY) by florian.drevet
 *  Contributors : florian.drevet
 *
 *  Train NeuralNetwork to recognize images of characters
 *
 */

#include "OCR_NN.h"

#include <dirent.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD
#include "neuralnetwork.h"
#include "NN_functions.h"
#include "../image.h"
#include <math.h>
#include <dirent.h>
=======
>>>>>>> a90bbd7a9de7e89a381c36699e1bdb171a9e3a30
#include <string.h>

#include "NN_functions.h"
#include "neuralnetwork.h"

/*!
 * Convert the most activated neuronne to the characters which is associated
 * @param neuralnetwork the neuralnetwork
 * @return the characters that the neuralnetwork think it is
 */
char output_to_char(struct NeuralNetwork neuralnetwork) {
    double *output = print_output(neuralnetwork);
    int neuronne_max = 0;
    double maxi_output = *output;
    for (int i = 0; i < (neuralnetwork.end - 1)->nbr_neuronnes; i++) {
        if (*output > maxi_output) {
            neuronne_max = i;
            maxi_output = *output;
        }
        output += 1;
    }
    switch (neuronne_max) {
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
void one_training(NeuralNetwork neuralnetwork, double *inputs, int len_inputs,
                  double waited_outputs[], double coeff) {
    feedForward(neuralnetwork, inputs, 625);
    backPropagation(neuralnetwork, waited_outputs);
    updateWeigth(neuralnetwork, inputs, len_inputs, coeff);
}

/*!
 * give the pointer to the beginning of a list of inputs for a neuralnetwork
 * from an image
 * @param img image from which the inputs are created
 * @return pointer the list of inputs
 * don't forget to free it
 */
double *inputs(Image *img) {
    double *inputs = malloc(25 * 25 * sizeof(double));
    double *in = inputs;
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            Uint8 r = 0;
            Uint8 g = 0;
            Uint8 b = 0;
            getPixelRGB(img, i, j, &r, &g, &b);
            double pixel_bi = (r + g + b) / (3 * 255);
            *in = pixel_bi;
            in += 1;
        }
    }
    return inputs;
}

/*!
 * Give the number of file in a folder.The result is associated to a struct
 * letter This function is use to creat the list of images used for the
 * training.
 * @param path the path of the folder
 * @param letter the struct letter that we want to add the number of file for a
 * path
 * @return the characters that the neuralnetwork think it is
 */
void nbr_pictures(char *path, Letter *letter) {
    int nbr = 0;
    struct dirent *ent = NULL;
    DIR *dir = opendir(path);
    while ((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, ".") !=
                0 &&  // the file is not the current folder
            strcmp(ent->d_name, "..") !=
                0)  // the file is not the parent folder
            nbr++;
    }

    letter->nbr_images = nbr;  // associate the number of file in the folder to
                               // the struct letter given
}

/*!
 * creat a pointer to a list of images that will be given to the training
 * fonction. It is all the images that are in a specific folder. The path of the
 * folder is in the struct letter. The result will be given to the struct letter
 * in its .img
 * @param letter the struct letter
 * the struct must have its .path and .nbr_file completed
 */
void creat_list_img(Letter *letter) {
    Image *list_img =
        malloc(letter->nbr_images *
               sizeof(Image));  // creat the memory space for all the images
    Image *l = list_img;
    struct dirent *lecture;
    DIR *rep;
    rep = opendir(letter->path);  // open the folder where images are

    while ((lecture = readdir(rep))) {
        if (strcmp(lecture->d_name, ".") != 0 &&
            strcmp(lecture->d_name, "..") != 0)
        // if the file is not the current folder or the father
        {
            char *s3 = NULL;  // the path of the file
            s3 = (char *)malloc(
                (strlen(letter->path) + strlen(lecture->d_name)) *
                sizeof(char));
            strcpy(s3, letter->path);
            strcat(s3, lecture->d_name);  // concatenation of the path of the
                                          // folder and the file name
            *l = loadImage(s3);           // load the image of the s3 path file
            *l = resize_images(*l);  // if the image has not the good dimension,
                                     // resized it (25x25 pixels)
            free(s3);  // free the memory given for the path string
            l++;
        }
    }
    letter->img = list_img;  // associated the pointer created to the letter.img
    closedir(rep);           // close the read of the file in the directory
}

/*!
 * Creat a struct letter
 * @param path the path of where are the img of this letter
 * @return the struct letter with .path, .img, .nbr_file initialized
 */
Letter creat_letter(char *path) {
    Letter letter;                // creat a struct letter
    letter.path = path;           // initialzed the .path
    nbr_pictures(path, &letter);  // initialized the .nbr_file
    // to use creat_list_img .path and .nbr_file must be initialized
    creat_list_img(&letter);  // initialized the .img
    return letter;
}

/*!
 * A test fonction to print the value of an array
 * this array is the waited value for a given letter
 * @param waited the array to print (contain all the waited value for all the
 * letters)
 * @param letter the letter we want to know the value
 * (this function is not use in the execution of the neuralnetwork)
 */
void print_waited(double waited[NBR_LETTER][NBR_LETTER], int letter) {
    printf("{");
    for (int i = 0; i < NBR_LETTER; i++) {
        printf("%f,", waited[letter][i]);
    }
    printf("}\n");
}

/*!
 * Train the NeuralNetwork
 * @param neuralnetwork the neuralnetwork to train
 * @param tab_letter the array with all the struct letter that the
 * neuralnetwork has to learn
 * @param len the size of the array
 * (the number of letter to learn)
 * @param waited array of the result of our neurlanetwork for each letter
 * @param times th enumber of tranning for the neuralnetwork
 * @param coeff the coeff for the backpropagation
 */
void training_NN(NeuralNetwork neuralnetwork, Letter tab_letter[DONE], int len,
                 double waited[NBR_LETTER][NBR_LETTER], int times,
                 double coeff) {
    // in a first time we creat all the data that the neuralnetwork will use to
    // learn we creat a tripple pointer that is each letter ->A->B->C-> ... the
    // double poiter is each image for each letter
    // ->A->ImgA1.png->ImgA2.png->... the last pointer is for each pixels of all
    // the images
    // ->A->ImgA1.png->1->0->1->0->...
    double ***img_pixels =
        malloc(len * sizeof(double) * 625 *
               331);  // creat the memory space for all the data
    // len is the number of letter (number of tripple pointer)
    // sizeof(double) is because each pixel are double
    // 625 is for the numbver of pixel and all images are of size 25x25,
    // thanks to the function resize_image us at the construction of struct
    // letter 331 the number of images for each letters
    double ***img_pixels_creation = img_pixels;
    // pointer to creat all the values without touch the begin of the pointer
    for (int i = 0; i < len; i++)  // for each letters to learn
    {
        int which_image =
            0;  // in order to know wich_image to creat the pointer of pixels
        double **images =
            malloc(sizeof(double) * 625 *
                   331);  // init the memory space for all the images
        // 625 for the number of pixels for each images
        // 331 for the number of images for each letters
        for (double **j = images; j < images + tab_letter[i].nbr_images; j++) {
            Image *img =
                tab_letter[i].img +
                which_image;  // the image to creat the pointer of pixels
            double *inputs_neuronnes = inputs(
                img);  // creat the pointer to all the pixel of the images
            *j = inputs_neuronnes;  // associated the pointer
            which_image += 1;       // next image of the folder
        }
        *img_pixels_creation = images;  // associated the pointer
        img_pixels_creation += 1;
    }

    for (int t = 0; t < times; t++)  // the number of trainning asked
    {
        int which_letter = 0;
        for (double ***i = img_pixels; i < img_pixels + len;
             i++)  // for each letters
        {
            for (double **j = *i; j < *i + tab_letter[which_letter].nbr_images;
                 j++)  // for each images
            {
                one_training(neuralnetwork, *j, 625, waited[which_letter],
                             coeff);  // do one trainning
            }
            which_letter += 1;
        }
        printf("%d\n", t);  // to see where we are in the trainning
    }
}

/*!
 * This function will be used in the OCR project
 * we give a image to our neuralnetwork and see what is its answer
 * by returning the char associated
 * @param neuralnetwork the neuralnetwork
 * @param img the image to know the letter
 * @return the char that the neuralnetwork thinks it is
 */
char print_res(NeuralNetwork neuralnetwork, Image img) {
    img = resize_images(img);  // resize the image to be 25x25 pixels
    double *inputs_list = inputs(&img);
    feedForward(neuralnetwork, inputs_list, 625);
    char res = output_to_char(neuralnetwork);
    return res;
}

/*!
 * Resize an image if it is not an 25x25 pixel one
 * @param img the imag to resize
 * @return the new image resized
 */
Image resize_images(Image img) {
    if (img.height < 25 || img.width < 25)  // if the image is too small
    {
        int decallage_x = (25 - img.width) / 2;   // to center the image with x
        int decallage_y = (25 - img.height) / 2;  // to center the image with y
        Image blanc = loadImage("src/NeuralNetwork_C/blanc.PNG");
        // load a white image of 25x25
        // the too small image will be put in the center of this white image
        for (int i = 0; i < img.width; i++) {
            for (int j = 0; j < img.height; j++) {
                Uint8 r = 0;
                Uint8 g = 0;
                Uint8 b = 0;
                getPixelRGB(&img, i, j, &r, &g,
                            &b);  // get the pixel(i, j) of the too small image
                Uint8 color[3] = {r, g, b};  // creat the color of this pixel
                setPixelColor(
                    &blanc, *color, decallage_x + i,
                    decallage_y + j);  // put the pixel in the white image
            }
        }
        return blanc;
    } else if (img.height >= 26 || img.width >= 26) {
        // if the image is too big
        Image blanc = loadImage(
            "/home/drevet/Documents/OCR_EPITA/src/NeuralNetwork_C/blanc.PNG");
        // as for too small we load a white image
        // there will be a lost of data
        // this part of the function is juste to avoid a crash of our
        // neurlanetwork
        for (int i = 0; i < blanc.width; i++) {
            for (int j = 0; j < blanc.height; j++) {
                Uint8 r = 0;
                Uint8 g = 0;
                Uint8 b = 0;
                getPixelRGB(&img, i, j, &r, &g, &b);
                Uint8 color[3] = {r, g, b};
                setPixelColor(&blanc, *color, i, j);
            }
        }
        return blanc;
    }

    return img;
}
