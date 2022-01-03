#ifndef _PROJECT_FILES_H
#define _PROJECT_FILES_H

#include "Project - header.h"

typedef unsigned char BYTE;

void saveListToBinFile(char* file_name, chessPosList* pos_list);

/*סעיף 6*/
int checkAndDisplayPathFromFile(char* file_name);
bool getListFromFile(FILE* bin_file, chessPosList* lst, short int* psize);
bool validMove(chessPos startingPosition, chessPos nextPosition);





#endif _PROJECT_FILES_H

