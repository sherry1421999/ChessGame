#ifndef _PROJECT_Q2_H
#define _PROJECT_Q2_H

#include "Project - header.h"

void display(chessPosList* lst);
void initializetable(Table table[][COLS]);
void removeNodeFromEnd(chessPosList* lst, chessPosCell* prev);
void removeNodeFromMiddle(chessPosCell* prev);
void updateTable(chessPosList* lst, Table table[][COLS]);
void printBoard(Table table[][COLS]);

#endif _PROJECT_Q2_H