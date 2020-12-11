/*!
<<<<<<< HEAD
=======
 *  /!\ DEPRECATED /!\
 * 
>>>>>>> 325a2fb694d9b09862640edd0a193487f93c7b60
 *  File created on 10/23/2020 (MM/DD/YYYY) by leo.duboin
 *  Contributors : leo.duboin
 * 
 *  This file contains all the necessary to implement a binary tree structure 
<<<<<<< HEAD
=======
 * 
 * 12/10/2020 : Created BoudaryBox and PixelLocation structs
>>>>>>> 325a2fb694d9b09862640edd0a193487f93c7b60
 */

#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include "../image.h"

// binaryTree.c --------------------

<<<<<<< HEAD
typedef struct BinTree {
    int key[2];
=======

typedef struct BinTree {
    BBox key;
>>>>>>> 325a2fb694d9b09862640edd0a193487f93c7b60
    struct BinTree *child;
    struct BinTree *sibling;
    struct BinTree *parent;
} BinTree;

<<<<<<< HEAD
BinTree createBinTree(int start, int end);
=======
BinTree createBinTree(BBox key);
>>>>>>> 325a2fb694d9b09862640edd0a193487f93c7b60
void addSibling(BinTree *new, BinTree *dest);
void addChild(BinTree *new, BinTree *dest);
void mapFunction(BinTree *tree, Image *image, void (*f)(Image *, BinTree *));
void printForest(BinTree *node);

<<<<<<< HEAD
=======

>>>>>>> 325a2fb694d9b09862640edd0a193487f93c7b60
#endif