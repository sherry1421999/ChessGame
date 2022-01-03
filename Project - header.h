#ifndef _PROJECT_HEADER_H
#define _PROJECT_HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#define ROWS 5
#define COLS 5
#define ERROR -1

#include <stdio.h>
#include <stdbool.h>
#include<stdlib.h>
#include <math.h>


typedef char chessPos[2];

typedef struct _chessPosArray {
	unsigned int size;
	chessPos* positions;
} chessPosArray;

typedef struct _chessPosCell {
	chessPos position;
	struct _chessPosCell* next;
} chessPosCell;

typedef struct _chessPosList {
	chessPosCell* head;
	chessPosCell* tail;
} chessPosList;

typedef struct _table {
	int value;
	bool exposed;
} Table;

typedef struct _treeNodeListCell;

typedef struct _treeNode {
	chessPos position;
	struct _treeNodeListCell* next_possible_position;// ����� ������ �� ���� ������ ���� ���� ������ �� ������
}treeNode;

typedef struct _treeNodeListCell {
	treeNode* node;// �� ������ ����� ������ �� ������ ����� ������ ���� ��� ���� ����
	struct _treeNodeListCell* next;// �� �������� ������ ����� ��� ��� ������
}treeNodeListCell;


typedef struct _pathTree {
	treeNode* root;
}pathTree;

/*���� 2*/
void display(chessPosList* lst);
void initializetable(Table table[][COLS]);
void updateTable(chessPosList* lst, Table table[][COLS]);
void printBoard(Table table[][COLS]);

/*���� 3*/
bool checkIfAllTrue(chessPosArray* arr, int size, bool path[][COLS]);

/*5 �-6*/
bool checkFile(FILE* f);

/*���� 7*/
void printMenu();
void startChessProject();
void getKnightStartingPosition(char* letterInput, char* numInput);
bool checkValidInput(char letterInput, char numInput);
char* getFileName();

void checkMemoryAllocation(void* arr);

#endif _PROJECT_HEADER_H