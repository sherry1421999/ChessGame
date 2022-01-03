#ifndef _PROJECT_Q4_H
#define _PROJECT_Q4_H

#include "Project - header.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
chessPosCell* findKnightPathCoveringAllBoardHelper(treeNode* root, int* psize);

void insertDataToStartList(chessPosList* lst, chessPos position);
void insertNodeToStartList(chessPosList* lst, chessPosCell* newLnode);
chessPosCell* createNewListNode(chessPos position, chessPosCell* next);
bool isEmptyList(chessPosList lst);
void makeEmptyList(chessPosList* lst);
void freeLst(chessPosList* lst);

#endif _PROJECT_Q4_H