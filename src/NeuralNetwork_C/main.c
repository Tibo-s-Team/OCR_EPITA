#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "neuralnetwork.h"
#include "NN_functions.h"
#include "../image.h"
#include "DataManipulation.h"
#include "OCR_NN.h"

double waited[NBR_LETTER][NBR_LETTER] = 
{
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //A
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //B
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //C
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //D
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //E
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //F
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //G
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //H
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //I
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //J
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //K
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //L
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //M
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //N
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //O
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //P
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //Q
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //R
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //S
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //T
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //U
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //V
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //W
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //X
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //Y
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //Z
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //a
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //b
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //c
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //d
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //e
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //f
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //g
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //h
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //i
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //j
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //k
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //l
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //m
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //n
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //o
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //p
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //q
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},   //r
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},   //s
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},   //t
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},   //u
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},   //v
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},   //w
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},   //x
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},   //y
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},   //z
    };


int main(int argc, char *argv[]) {
    srand(time (NULL));
    // int layer[4] = {16, 16, 16, DONE};
    // NeuralNetwork neuralnetwork2 = creat_neuralNetwork(625, layer, 4);
    // print_output(neuralnetwork2);
   
    //save(neuralnetwork, "/home/drevet/Documents/OCR_EPITA/tests/OCR_test5");
    NeuralNetwork neuralnetwork2 = load("/home/drevet/Documents/OCR_EPITA/tests/OCR_Finale_1_letter1");
    Image img = loadImage("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/t/t.PNG");
    char res2 = print_res(neuralnetwork2, img);
    //char res = print_res(neuralnetwork2, "/home/drevet/Documents/OCR_EPITA/tests/images/test_letters/A.png");
    printf("RES = %d\n", res2);
    printf("RES WAITED %d\n", 't');
    printf("%c\n", res2);

    Letter letter_A = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/A/");
    Letter letter_B = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/B/");
    Letter letter_C = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/C/");
    Letter letter_D = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/D/");
    Letter letter_E = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/E/");
    Letter letter_F = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/F/");
    Letter letter_G = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/G/");
    Letter letter_H = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/H/");
    Letter letter_I = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/I/");
    Letter letter_J = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/J/");
    Letter letter_K = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/K/");
    Letter letter_L = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/L/");
    Letter letter_M = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/M/");
    Letter letter_N = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/N/");
    Letter letter_O = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/O/");
    Letter letter_P = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/P/");
    Letter letter_Q = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/Q/");
    Letter letter_R = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/R/");
    Letter letter_S = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/S/");
    Letter letter_T = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/T/");
    Letter letter_U = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/U/");
    Letter letter_V = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/V/");
    Letter letter_W = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/W/");
    Letter letter_X = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/X/");
    Letter letter_Y = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/Y/");
    Letter letter_Z = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/Z/");
    Letter letter_a = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/a/");
    Letter letter_b = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/b/");
    Letter letter_c = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/c/");
    Letter letter_d = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/d/");
    Letter letter_e = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/e/");
    Letter letter_f = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/f/");
    Letter letter_g = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/g/");
    Letter letter_h = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/h/");
    Letter letter_i = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/i/");
    Letter letter_j = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/j/");
    Letter letter_k = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/k/");
    Letter letter_l = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/l/");
    Letter letter_m = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/m/");
    Letter letter_n = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/n/");
    Letter letter_o = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/o/");
    Letter letter_p = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/p/");
    Letter letter_q = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/v/");
    Letter letter_w = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/w/");
    Letter letter_x = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/q/");
    Letter letter_r = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/r/");
    Letter letter_s = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/s/");
    Letter letter_t = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/t/");
    Letter letter_u = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/u/");
    Letter letter_v = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/x/");
    Letter letter_y = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/y/");
    Letter letter_z = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters - Copy/letter/z/");


    // Letter letter_A = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/A/", 'A');
    // Letter letter_B = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/B/", 'B');
    // Letter letter_C = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/C/", 'C');
    // Letter letter_D = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/D/", 'D');
    // Letter letter_E = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/E/", 'E');
    // Letter letter_F = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/F/", 'F');
    // Letter letter_G = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/G/", 'G');
    // Letter letter_H = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/H/", 'H');
    // Letter letter_I = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/I/", 'I');
    // Letter letter_J = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/J/", 'J');
    // Letter letter_K = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/K/", 'K');
    // Letter letter_L = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/L/", 'L');
    // Letter letter_M = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/M/", 'M');
    // Letter letter_N = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/N/", 'N');
    // Letter letter_O = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/O/", 'O');
    // Letter letter_P = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/P/", 'P');
    // Letter letter_Q = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/Q/", 'Q');
    // Letter letter_R = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/R/", 'R');
    // Letter letter_S = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/S/", 'S');
    // Letter letter_T = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/T/", 'T');
    // Letter letter_U = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/U/", 'U');
    // Letter letter_V = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/V/", 'V');
    // Letter letter_W = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/W/", 'W');
    // Letter letter_X = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/X/", 'X');
    // Letter letter_Y = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/Y/", 'Y');
    // Letter letter_Z = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/Z/", 'Z');
    // Letter letter_a = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/a/", 'a');
    // Letter letter_b = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/b/", 'b');
    // Letter letter_c = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/c/", 'c');
    // Letter letter_d = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/d/", 'd');
    // Letter letter_e = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/e/", 'e');
    // Letter letter_f = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/f/", 'f');
    // Letter letter_g = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/g/", 'g');
    // Letter letter_h = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/h/", 'h');
    // Letter letter_i = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/i/", 'i');
    // Letter letter_j = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/j/", 'j');
    // Letter letter_k = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/k/", 'k');
    // Letter letter_l = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/l/", 'l');
    // Letter letter_m = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/m/", 'm');
    // Letter letter_n = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/n/", 'n');
    // Letter letter_o = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/o/", 'o');
    // Letter letter_p = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/p/", 'p');
    // Letter letter_q = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/v/", 'q');
    // Letter letter_w = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/w/", 'r');
    // Letter letter_x = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/q/", 's');
    // Letter letter_r = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/r/", 't');
    // Letter letter_s = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/s/", 'u');
    // Letter letter_t = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/t/", 'v');
    // Letter letter_u = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/u/", 'w');
    // Letter letter_v = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/x/", 'x');
    // Letter letter_y = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/y/", 'y');
    // Letter letter_z = creat_letter("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/z/", 'z');

    Letter letters[DONE] = {letter_A,
                            letter_B,
                            letter_C, 
                            letter_D, 
                            letter_E, 
                            letter_F, 
                            letter_G, 
                            letter_H, 
                            letter_I, 
                            letter_J,
                            letter_K,
                            letter_L,
                            letter_M,
                            letter_N,
                            letter_O,
                            letter_P,
                            letter_Q,
                            letter_R,
                            letter_S,
                            letter_T,
                            letter_U,
                            letter_V,
                            letter_W,
                            letter_X,
                            letter_Y,
                            letter_Z,
                            letter_a,
                            letter_b,
                            letter_c,
                            letter_d,
                            letter_e,
                            letter_f,
                            letter_g,
                            letter_h,
                            letter_i,
                            letter_j,
                            letter_k,
                            letter_l,
                            letter_m,
                            letter_n,
                            letter_o,
                            letter_p,
                            letter_q,
                            letter_r,
                            letter_s,
                            letter_t,
                            letter_u,
                            letter_v,
                            letter_w,
                            letter_x,
                            letter_y,
                            letter_z};
    
    //training_NN(neuralnetwork2, letters, DONE, waited, 20000, 0.1);
    //save(neuralnetwork2, "/home/drevet/Documents/OCR_EPITA/tests/OCR_Finale_1_letter1");
    //Image img2 = loadImage("/home/drevet/Documents/OCR_EPITA/tests/images/letters/letter/r/r.PNG");
    Image img2 = loadImage("/home/drevet/Documents/OCR_EPITA/tests/images/test_letters/e.PNG");
    char res = print_res(neuralnetwork2, img2);
    //char res = print_res(neuralnetwork2, "/home/drevet/Documents/OCR_EPITA/tests/images/letters/A/A.PNG");
    //char res = print_res(neuralnetwork2, "/home/drevet/Documents/OCR_EPITA/tests/images/test_letters/A.png");
    printf("RES = %d\n", res);
    printf("RES WAITED %d\n", 't');
    printf("%c\n", res);
    free_neuralNetwork(neuralnetwork2);
    return 0;
}
