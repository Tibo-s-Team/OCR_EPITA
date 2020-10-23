/*!
 *  Binary tree implementation applied to store blocks of text.
 *  By construction the keys will automaticaly be sorted in increasing order.
 * 
 *  Key : int tuple (start, end) representing the start and the end of a block.
 */

#include "segmentation.h"

// Creates a new node with the given key elements.
BinTree createBinTree(int start, int end) {
    BinTree node = {{start, end}, NULL, NULL};
    return node;
}

// Appends a new node as a sibling of a leaf.
// By consruction the leaves are added in increasing order.
void appendBinTree(BinTree *new, BinTree *dest) {
    while (!dest->sibling) dest = dest->sibling;
    dest->sibling = new;
}

// apply a function to every leaf of the tree
void mapFunction(BinTree *tree, void (*f)(BinTree *)) {
    if (tree) {
        if (tree->child)
            mapFunction(tree->child, f);
        else {
            (*f)(tree);
            mapFunction(tree->sibling, f);
        }
    }
}