#ifndef _PROJECT_LISTS_H
#define _PROJECT_LISTS_H

#include "Project - header.h"
/*���� 2*/
void removeNodeFromEnd(chessPosList* lst, chessPosCell* prev);
void removeNodeFromMiddle(chessPosCell* prev);

/*���� 3*/
void insertTreeNodeToStartLst(treeNodeListCell* lst, treeNodeListCell* newLnode);
treeNodeListCell* insertDataToStartChildList(treeNodeListCell* Lnode, treeNode* Tnode);
treeNodeListCell* createNewListCell(treeNode* Tnode, treeNodeListCell* next);

/*���� 4*/
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
chessPosCell* findKnightPathCoveringAllBoardHelper(treeNode* root, int* psize);

void insertDataToStartList(chessPosList* lst, chessPos position);
void insertNodeToStartList(chessPosList* lst, chessPosCell* newLnode);
chessPosCell* createNewListNode(chessPos position, chessPosCell* next);
bool isEmptyList(chessPosList lst);
void makeEmptyList(chessPosList* lst);
void freeLst(chessPosList* lst);

/*���� 6*/
void insertDataToEndList(chessPosList* lst, chessPos position);
void insertNodeToEndList(chessPosList* lst, chessPosCell* newLnode);
int getCurrListSize(chessPosList* lst);
bool pathCoveringAllBoard(int listSize);
void printList(chessPosList* lst);

#endif _PROJECT_LISTS_H

