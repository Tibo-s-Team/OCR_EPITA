#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "neuralnetwork.h"

int main(int argc, char *argv[]) {
    Layer layer = creat_layer(5, 3);
    free_layer(layer);
    return 0;
}
