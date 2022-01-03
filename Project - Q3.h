#ifndef _PROJECT_Q3_H
#define _PROJECT_Q3_H
#include "Project - header.h"
#include "Project - Q1.h"

pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
treeNode* findAllPossibleKnightPathshelper(chessPos* startingPosition, chessPosArray*** mat, bool path[][COLS]);
void initializePathTable(bool table[][COLS]);
bool checkIfAllTrue(chessPosArray* arr, int size, bool path[][COLS]);

treeNode* createNewTreeNode(chessPos* startingPosition);
void insertTreeNodeToStartLst(treeNodeListCell* lst, treeNodeListCell* newLnode);
treeNodeListCell* insertDataToStartChildList(treeNodeListCell* Lnode, treeNode* Tnode);
treeNodeListCell* createNewListCell(treeNode* Tnode, treeNodeListCell* next);

void printPathTree(pathTree tr);
void printPathTreeRec(treeNode* root, int level);

#endif _PROJECT_Q3_H