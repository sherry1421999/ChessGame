#ifndef _PROJECT_TREES_H
#define _PROJECT_TREES_H

#include "Project - header.h"

/*סעיף 3*/
pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
treeNode* findAllPossibleKnightPathshelper(chessPos* startingPosition, chessPosArray*** mat, bool path[][COLS]);

treeNode* createNewTreeNode(chessPos* startingPosition);

void printPathTree(pathTree tr);
void printPathTreeRec(treeNode* root, int level);







#endif _PROJECT_TREES_H
