/*!
 *  File created on 10/23/2020 (MM/DD/YYYY) by leo.duboin
 *  Contributors : leo.duboin
 * 
 *  This file contains all the necessary to implement a binary tree structure 
 */

#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include "../image.h"

// binaryTree.c --------------------

typedef struct BinTree {
    int key[2];
    struct BinTree *child;
    struct BinTree *sibling;
    struct BinTree *parent;
} BinTree;

BinTree createBinTree(int start, int end);
void addSibling(BinTree *new, BinTree *dest);
void addChild(BinTree *new, BinTree *dest);
void mapFunction(BinTree *tree, Image *image, void (*f)(Image *, BinTree *));
void printForest(BinTree *node);

#endif