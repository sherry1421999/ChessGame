#include "Project - Q1.h"

/******************************************** ValidKnightMoves ***************************************************************
The function Returns a two-dimensional array of pointers to possible placement arrays for a cavalry motion.
Each cell in row R and column C will contain an array of locations to which it is allowed to interpret to move from that cell.
******************************************************************************************************************************/
chessPosArray*** ValidKnightMoves()
{
	int i, j;

	chessPosArray*** chessArray = (chessPosArray***)malloc(sizeof(chessPosArray**) * ROWS);
	checkMemoryAllocation(chessArray);
	for (i = 0; i < ROWS; i++)
	{
		chessArray[i] = (chessPosArray**)malloc(sizeof(chessPosArray*) * ROWS);
		checkMemoryAllocation(chessArray[i]);

	}
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++)
		{
			chessArray[i][j] = positions(i, j);
		}
	}
	return chessArray;
}

/******************************************** positions ***************************************************************
The function allocate and put in arr the optional locations from every point in the table.
******************************************************************************************************************************/
chessPosArray* positions(int r, int c)
{
	int size = 0;

	chessPosArray* pos = (chessPosArray*)malloc(sizeof(chessPosArray));
	checkMemoryAllocation(pos);
	chessPos* positions = (chessPos*)malloc(sizeof(chessPos) * 8);
	checkMemoryAllocation(positions);

	if (c + 2 < COLS)
	{
		if (r + 1 < ROWS)
		{
			positions[size][0] = 'A' + (r + 1);
			positions[size][1] = '1' + (c + 2);
			size++;
		}
		if (r - 1 >= 0)
		{
			positions[size][0] = 'A' + (r - 1);
			positions[size][1] = '1' + (c + 2);
			size++;
		}
	}
	if (c - 2 >= 0)
	{
		if (r + 1 < ROWS)
		{
			positions[size][0] = 'A' + (r + 1);
			positions[size][1] = '1' + (c - 2);
			size++;
		}
		if (r - 1 >= 0)
		{
			positions[size][0] = 'A' + (r - 1);
			positions[size][1] = '1' + (c - 2);
			size++;
		}
	}
	if (r + 2 < ROWS)
	{
		if (c + 1 < COLS)
		{
			positions[size][0] = 'A' + (r + 2);
			positions[size][1] = '1' + (c + 1);
			size++;
		}
		if (c - 1 >= 0)
		{
			positions[size][0] = 'A' + (r + 2);
			positions[size][1] = '1' + (c - 1);
			size++;
		}
	}
	if (r - 2 >= 0)
	{
		if (c + 1 < COLS)
		{
			positions[size][0] = 'A' + (r - 2);
			positions[size][1] = '1' + (c + 1);
			size++;
		}
		if (c - 1 >= 0)
		{
			positions[size][0] = 'A' + (r - 2);
			positions[size][1] = '1' + (c - 1);
			size++;
		}
	}

	positions = (chessPos*)realloc(positions, sizeof(chessPos) * size);
	pos->positions = positions;
	pos->size = size;
	return pos;
}

/******************************************** checkMemoryAllocation ***************************************************************
The function checks if the allocation is succeded.
******************************************************************************************************************************/
void checkMemoryAllocation(void* arr)
{
	if (arr == NULL)
	{
		printf("Allocation error\n");
		exit(1);
	}
}