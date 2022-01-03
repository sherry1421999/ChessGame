#include "Project - header.h"
#include "Project - Q7.h"


void getUsersChoice()
{
	chessPos startingPosition = NULL;
	pathTree possibleMovesTree;
	chessPosList* coveringAllBoard;
	int userchoice;

	printMenu();
	scanf("%d", &userchoice);

	switch (userchoice)
	{
	case 1:
		getKnightStartingPosition(&startingPosition[0], &startingPosition[1]);
		printMenu();
		break;
	case 2:
		if (enterPosition(startingPosition) == true)
			possibleMovesTree = findAllPossibleKnightPaths(&startingPosition);
		break;
	case 3:
		if (enterPosition(startingPosition) == true)
			coveringAllBoard = findKnightPathCoveringAllBoard(&possibleMovesTree);
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		exit(1);
		break;
	}

}

void getKnightStartingPosition(char* letterInput, char* numInput)
{
	char letter, digit;

	printf("Please enter a knight's starting position.\n");
	scanf("%c%c", &letter, &digit);

	if (checkValidInput(letter, digit) == false)
		getKnightStartingPosition(letterInput, numInput);
	else
	{
		*letterInput = letter;
		*numInput = digit;
	}
}


bool checkValidInput(char letterInput, char numInput)
{
	if ((letterInput < 'A' && letterInput > 'H') || (numInput < '1' && numInput > '8'))
	{
		printf("Invalid Input.\n Please enter an uppercase letter between A to H and a number between 1 to 8.");
		return false;
	}
	else
		return true;	
}

bool enterPosition(chessPos startingPosition)
{
	if (startingPosition == NULL)
	{
		printf("You must first enter a knight's starting position!\nPlease return to option 1 on the menu.\n");
		printMenu();
		return false;
	}
	else
		return true;
		
}

void printMenu()
{
	printf("1. Enter a knight's starting position");
	printf("2. Creat all possible knight paths");
	printf("3. Finf a knight path covering all board to file");
	printf("4. Save knight path covering all board to file");
	printf("5. Load and display path from file");
	printf("6. Exit");
}