/*!
 *  /!\ DEPRECATED /!\
 * 
 *  File created on 10/23/2020 (MM/DD/YYYY) by leo.duboin
 *  Contributors : leo.duboin
 * 
 *  This file contains all the necessary to implement a binary tree structure 
 * 
 * 12/10/2020 : Created BoudaryBox and PixelLocation structs
 */

#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include "../Image/image.h"

// binaryTree.c --------------------


typedef struct BinTree {
    BBox key;
    struct BinTree *child;
    struct BinTree *sibling;
    struct BinTree *parent;
} BinTree;

BinTree createBinTree(BBox key);
void addSibling(BinTree *new, BinTree *dest);
void addChild(BinTree *new, BinTree *dest);
void mapFunction(BinTree *tree, Image *image, void (*f)(Image *, BinTree *));
void printForest(BinTree *node);


#endif