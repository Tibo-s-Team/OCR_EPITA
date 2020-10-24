/*!
 *  Binary tree implementation applied to store blocks of text.
 *  By construction the keys will automaticaly be sorted in increasing order.
 *
 *  Key : int tuple (start, end) representing the start and the end of a block.
 */

#include "segmentation.h"

// Creates a new node with the given key elements.
BinTree createBinTree(int start, int end) {
    BinTree node = {{start, end}, NULL, NULL, NULL};
    return node;
}

// Appends a new node as a sibling of a leaf.
// By consruction the leaves are added in increasing order.
void addSibling(BinTree *new, BinTree *dest) {
    if (dest->sibling == NULL) {
        dest->sibling = new;
        new->parent = dest->parent;
    } else
        addSibling(new, dest->sibling);
}

// Add a new child to a tree if it has none
void addChild(BinTree *new, BinTree *dest) {
    if (dest->child == NULL) {
        new->parent = dest;
        dest->child = new;
    }
}

// apply a function to every leaf of the tree
void mapFunction(BinTree *tree, Image *image, void (*f)(Image *, BinTree *)) {
    if (tree != NULL) {
        if (tree->child != NULL)
            mapFunction(tree->child, image, f);
        else {
            (*f)(image, tree);
            mapFunction(tree->sibling, image, f);
        }
    }
}

void printBranch(BinTree *node) {
    if (node != NULL) {
        printf("[%d, %d]\n", node->key[0], node->key[1]);
        printBranch(node->sibling);
    }
}