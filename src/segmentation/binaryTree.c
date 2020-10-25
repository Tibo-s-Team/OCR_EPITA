/*!
 *  File created on 10/23/2020 (MM/DD/YYYY) by leo.duboin
 *  Contributors : leo.duboin
 *
 *  Binary tree implementation applied to store information about blocks of
 * text. By construction the keys in a forest will automaticaly be sorted in
 * increasing order.
 *
 *  Key : int tuple (start, end) representing the start and the end of a block.
 */

#include "binaryTree.h"

/*!
 * Create a new node with the given key elements.
 * @param start starting position of a block
 * @param end ending position of a block
 * @return a standalone tree whose key contains the position of a block
 */
BinTree createBinTree(int start, int end) {
    BinTree node = {{start, end}, NULL, NULL, NULL};
    return node;
}

/*!
 * Append a new node as a sibling of an existing one.
 *  By consruction the nodes are added in increasing order.
 * @param new the tree to add as a sibling
 * @param dest the tree to add a sibling to
 */
void addSibling(BinTree *new, BinTree *dest) {
    if (dest->sibling == NULL) {
        dest->sibling = new;
        new->parent = dest->parent;
    } else
        addSibling(new, dest->sibling);
}

/*!
 * Add a new child to a tree if it has none.
 * @param new the tree to add as a child
 * @param des the tree to add a child to
 */
void addChild(BinTree *new, BinTree *dest) {
    if (dest->child == NULL) {
        new->parent = dest;
        dest->child = new;
    }
}
/*!
 * Apply a function to every leaf of the tree
 * @param tree the tree whose leaves the function will be applied on
 * @param image black and white image which the funtion will use
 * @param f a function to apply on each of the tree's leaves
 */
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

/*!
 * Print the content of a forest of trees. Each node is printed as [key1, key2].
 * @param node the first tree of the forest to be printed
 */
void printForest(BinTree *node) {
    if (node != NULL) {
        printf("[%d, %d]\n", node->key[0], node->key[1]);
        printForest(node->sibling);
    }
}