#include "Project - Q2.h"

/******************************************** display ***************************************************************
The function receives a list of squares. First, the function removes from a list of repetitive squares.
After you remove the repetitive squares, the function displays the remaining squares in the list on the screen within
a table in order.
*********************************************************************************************************************/
void display(chessPosList* lst)
{
	Table board[ROWS][COLS];
	int row, col;

	chessPosCell* curr = lst->head, * prev = curr;
	initializetable(board);

	while (curr != NULL)
	{
		row = (int)curr->position[0] - 'A';
		col = (int)curr->position[1] - '1';
		if (board[row][col].exposed == false)
		{
			board[row][col].exposed = true;
		}
		else
		{
			if (curr->next == NULL)
				removeNodeFromEnd(lst, prev);
			else
				removeNodeFromMiddle(prev);
		}
		prev = curr;
		curr = curr->next;
	}
	printf("\n");
	updateTable(lst, board);

}

/******************************************** initializetable *******************************************************
The function initializing the board to 0 and false.
*********************************************************************************************************************/
void initializetable(Table table[][COLS])
{
	int i, j;
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++)
		{
			table[i][j].value = 0;
			table[i][j].exposed = false;
		}
	}
}

/******************************************** removeNodeFromEnd *****************************************************
The function removes node from thr end of the list
*********************************************************************************************************************/
void removeNodeFromEnd(chessPosList* lst, chessPosCell* prev)
{
	chessPosCell* to_remove = prev->next;

	prev->next = NULL;
	lst->tail = prev;
	free(to_remove);
}
/******************************************** removeNodeFromMiddle *****************************************************
The function removes node from thr middle of the list.
*********************************************************************************************************************/
void removeNodeFromMiddle(chessPosCell* prev)
{
	chessPosCell* to_remove = prev->next;

	prev->next = to_remove->next;
	free(to_remove);
}

/******************************************** updateTable *****************************************************
The function updates the table by the points in the list.
*********************************************************************************************************************/
void updateTable(chessPosList* lst, Table table[][COLS])
{
	chessPosCell* curr = lst->head;
	int i, j, value = 1;

	while (curr)
	{
		i = curr->position[0] - 'A';
		j = curr->position[1] - '1';
		table[i][j].value = value;
		value++;
		curr = curr->next;
	}
	printBoard(table);
}
/******************************************** updateTable *****************************************************
The function prints the board.
*********************************************************************************************************************/
void printBoard(Table table[][COLS])
{

	int i, j;

	for (i = 0; i <= COLS; i++)
	{
		if (i == 0)
			printf("%6c" ,' ');
		else
			printf("%5d", i);
	}
	printf("\n");
	printf("   ______________________________\n");
	for (i = 0; i < ROWS; i++)
	{
		printf("%5c |", 'A' + i);
		for (j = 0; j < COLS; j++)
		{
			if (!table[i][j].exposed)
			{
				printf("%5c|", ' ', table[i][j].value);
			}
			else
				printf("%4d|", table[i][j].value);
		}
		printf("\n   ______________________________\n");
		
	}

}

