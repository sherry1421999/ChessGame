#include "Project - Q6.h"
#include "Project - Q4.h"
#include "Project - Q1.h"

int checkAndDisplayPathFromFile(char* file_name)
{
	FILE* bin_file = fopen(file_name, "rb");
	checkFile(bin_file);

	chessPosList pathList;
	makeEmptyList(&pathList);

	short int list_size;

	chessPosArray*** validPosArray = ValidKnightMoves();

	if (getListFromFile(bin_file, validPosArray, &pathList, &list_size) == false)
		return 1;
	else
	{

	}


	
}

bool getListFromFile(FILE* bin_file,chessPosArray*** validMoves, chessPosList* lst ,short int* psize)
{
	short int list_size;
	fread(&list_size, sizeof(short int), 1, bin_file);
	*psize = list_size;

	BYTE first, second, third;
	chessPos curr_position;
	int i;
	BYTE mask1 = 0x07;

	for (i = 0; i < list_size; i += 4)
	{
		fread(&first, sizeof(BYTE), 1, bin_file);
		curr_position[0] = first >> 5;
		curr_position[1] = first >> 2 & mask1;
		insertDataToEndList(lst, curr_position);

		fread(&second, sizeof(BYTE), 1, bin_file);
		curr_position[0] = (first << 1 & mask1) | second >> 7;
		curr_position[1] = second >> 4 & mask1;
		insertDataToEndList(lst, curr_position);

		fread(&third, sizeof(BYTE), 1, bin_file);
		curr_position[0] = second >> 1 & mask1;
		curr_position[1] = (second << 2 & mask1) | third >> 6;
		insertDataToEndList(lst, curr_position);

		curr_position[0] = third >> 3 & mask1;
		curr_position[1] = third & mask1;
		insertDataToEndList(lst, curr_position);
	}

}


void insertDataToEndList(chessPosList* lst, chessPos position)
{
	chessPosCell* newLnode = createNewListNode(position, NULL);
	insertNodeToStartList(lst, newLnode);
}

chessPosCell* createNewListNode(chessPos position, chessPosCell* next)
{
	chessPosCell* newLnode = (chessPosCell*)malloc(sizeof(chessPosCell));
	checkMemoryAllocation(newLnode);

	newLnode->position[0] = position[0];
	newLnode->position[1] = position[1];
	newLnode->next = next;

	return newLnode;
}

void insertNodeToEndList(chessPosList* lst, chessPosCell* newLnode)
{
	if (isEmptyList(*lst))
		lst->head = lst->tail = newLnode;
	else
	{
		lst->tail->next = newLnode;
		lst->tail = newLnode;
	}
}

void checkFile(FILE* f)
{
	if (f == NULL)
	{
		printf("Opening file failed!\n");
		exit(-1);
	}
}