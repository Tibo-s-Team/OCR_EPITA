/*
 * File created by Léo DUBOIN on 12/11/2020.
 * 
 * Simple implementation of a BoundaryBox structure.
 * Used to identify an area inside an image.
*/

#include "boundaryBox.h"

/*!
 * Prints information about a BoundaryBox
 * @param box the BoundaryBox structure we want to be displayed.
 */
void printBox(BBox box) {
    printf("[%d, %d] -> [%d,%d]\n", box.start.x, box.start.y, box.end.x,
           box.end.y);
}