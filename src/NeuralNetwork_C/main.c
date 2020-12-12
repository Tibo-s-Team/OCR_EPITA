#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "neuralnetwork.h"
#include "NN_functions.h"
#include "../image.h"
#include "OCR_NN.h"
#define A = {1, 0, 0}

char print_res(NeuralNetwork neuralnetwork ,char* path)
{
    Image img = loadImage(path);
    double *inputs_list = inputs(&img);
    feedForward(neuralnetwork, inputs_list, 625);
    return output_to_char(neuralnetwork);
}

int main(int argc, char *argv[]) {
    srand(time (NULL));
    int layer[3] = {16, 16, 3};
    NeuralNetwork neuralnetwork = creat_neuralNetwork(625, layer, 3);

    double waited_A[NBR_LETTER] = {1, 0, 0};
    double waited_B[NBR_LETTER] = {1, 0, 0};
    double waited_C[NBR_LETTER] = {1, 0, 0};
    double waited[NBR_LETTER][NBR_LETTER] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    Letter letter_A = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/A/");
    Letter letter_B = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/B/");
    Letter letter_C = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/C/");
    Letter letters[NBR_LETTER] = {letter_A, letter_B, letter_C};
    training_NN(neuralnetwork, letters, NBR_LETTER, waited, 1000000000, 0.1);
    char res = print_res(neuralnetwork, "/home/drevet/Documents/OCR_EPITA/tests/images/letters/C/c20.png");
    printf("RES = %d\n", res);
    printf("RES WAITED %d\n", 'C');
    free_neuralNetwork(neuralnetwork);
    return 0;
}
