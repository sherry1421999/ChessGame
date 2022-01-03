#include "Project - header.h"
#include "Project - Q5.h"

int checkAndDisplayPathFromFile(char* file_name);
bool getListFromFile(FILE* bin_file, chessPosList* lst, short int* psize);
bool validMove(chessPos startingPosition, chessPos nextPosition);
int getCurrListSize(chessPosList* lst);
bool pathCoveringAllBoard(int listSize);

void insertDataToEndList(chessPosList* lst, chessPos position);
chessPosCell* createNewListNode(chessPos position, chessPosCell* next);
void insertNodeToEndList(chessPosList* lst, chessPosCell* newLnode);
void printList(chessPosList* lst);