#include "Project - header.h"
#include "Project - Trees.h"
#include "Project - Files.h"

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
			printf("%6c", ' ');
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

/******************************************** checkIfAllTrue *****************************************************
The function checks if the path already pathed the childrens. if all the children are true it return true.
******************************************************************************************************************/
bool checkIfAllTrue(chessPosArray* arr, int size, bool path[][COLS])
{
	int i, row, col;
	bool isAllTrue = true;

	for (i = 0; i < size && isAllTrue == true; i++)
	{
		row = arr->positions[i][0] - 'A';
		col = arr->positions[i][1] - '1';

		if (path[row][col] == false)
			isAllTrue = false;
	}
	return isAllTrue;
}

/********* checkFile **********************
The function receives a file and checks if the file opening was successful.
***************************************************/
bool checkFile(FILE* f)
{
	if (f == NULL)
	{
		printf("Opening file failed!\n");
		return false;
	}
	else
		return true;
}

/******************************************** printMenu *****************************************************
The function prints the menu.
******************************************************************************************************************/
void printMenu()
{
	printf("1. Enter a knight's starting position.\n");
	printf("2. Creat all possible knight paths.\n");
	printf("3. Finf a knight path covering all board to file.\n");
	printf("4. Save knight path covering all board to file.\n");
	printf("5. Load and display path from file.\n");
	printf("6. Exit.\n");
}

/******************************************** startChessProject *****************************************************
The function creates a menu that displays all the options given to the user.
******************************************************************************************************************/
void startChessProject()
{
	chessPos startingPosition = { NULL };
	pathTree possibleMovesTree;
	chessPosList* coveringAllBoard = NULL;
	char* file_name;
	bool coveringopen, chosenpoint, thereistree;

	int userchoice = 0;
	coveringopen = chosenpoint = thereistree = false;

	while (userchoice != 6)
	{
		printMenu();
		scanf("%d", &userchoice);
		if (userchoice > 1 && userchoice < 5 && chosenpoint == false)
		{
			getKnightStartingPosition(&startingPosition[0], &startingPosition[1]);
			chosenpoint = true;
		}
		if (userchoice == 3 || userchoice == 4)
		{
			if (!thereistree)
			{
				possibleMovesTree = findAllPossibleKnightPaths(startingPosition);
				thereistree = true;
			}
			if (!coveringopen)
			{
				coveringAllBoard = findKnightPathCoveringAllBoard(&possibleMovesTree);
				if (coveringAllBoard == NULL)
					printf("There is no knight path that covering all board.\n Please enter different position.\n\n");
				else
					coveringopen = true;
			}
		}

		switch (userchoice)
		{
		case 1:
			coveringopen = chosenpoint = thereistree = false;
			getKnightStartingPosition(&startingPosition[0], &startingPosition[1]);
			chosenpoint = true;
			break;
		case 2:
			if (!thereistree)
			{
				possibleMovesTree = findAllPossibleKnightPaths(startingPosition);
				thereistree = true;
			}
			break;
		case 3:
			break;
		case 4:
			if (coveringAllBoard == NULL)
				break;
			file_name = getFileName();
			saveListToBinFile(file_name, coveringAllBoard);
			break;
		case 5:
			file_name = getFileName();
			checkAndDisplayPathFromFile(file_name);
			break;
		default:
			printf("Invalid choice! please enter a digit between 1 to 6.\n\n");
			break;
		}
	}
	exit(1);
}

/******************************************** getKnightStartingPosition *****************************************************
The function receives from the user the input for the knight position.
******************************************************************************************************************/
void getKnightStartingPosition(char* letterInput, char* numInput)
{
	char letter, digit;

	printf("Please enter a knight's starting position.\n");
	scanf(" %c%c", &letter, &digit);

	while (checkValidInput(letter, digit) == false)
		getKnightStartingPosition(&letter, &digit);

	*letterInput = letter;
	*numInput = digit;
}

/******************************************** checkValidInput *****************************************************
The function checks if the users input is valid. if not- returns false.
******************************************************************************************************************/
bool checkValidInput(char letterInput, char numInput)
{
	if ((letterInput < 'A' || letterInput > 'H') || (numInput < '1' || numInput > '8'))
	{
		printf("Invalid Input.\n");
		return false;
	}
	else
		return true;
}

/******************************************** getFileName *****************************************************
The function receives a file name from the user, and assigns a string accordingly.
******************************************************************************************************************/
char* getFileName()
{
	char* file_name;
	int log_size = 0, phy_size = 1;
	char c = '\0';

	printf("Please enter file name.\n");
	file_name = (char*)malloc(sizeof(char) * phy_size);
	checkMemoryAllocation(file_name);
	scanf(" %c", &c);

	while (c != '\n')
	{
		if (log_size == phy_size)
		{
			phy_size *= 2;
			file_name = realloc(file_name, sizeof(char) * phy_size);
			checkMemoryAllocation(file_name);
		}
		file_name[log_size] = c;
		log_size++;
		scanf("%c", &c);
	}

	file_name = realloc(file_name, sizeof(char) * log_size + 1);
	checkMemoryAllocation(file_name);
	file_name[log_size] = '\0';

	return file_name;
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