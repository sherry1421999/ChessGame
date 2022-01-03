#include "Project - Files.h"

/********* saveListToBinFile **********************
The function receives as input a positions list and name of a binary file and saves those positions into the file.
At the beginning of the file a number of short type will be stored that represents the number of locations in the list.
each location is represented by 6 bits. (So that in all three bytes exactly 4 locations will be saved).
***************************************************/
void saveListToBinFile(char* file_name, chessPosList* pos_list)
{
	unsigned short int list_size = 0;
	FILE* bin_file = fopen(file_name, "wb");
	checkFile(bin_file);
	fseek(bin_file, sizeof(unsigned short int), SEEK_SET);

	chessPosCell* curr = pos_list->head;
	while (curr)
	{
		BYTE arr[3], mask = 0x00;
		int curr_row, curr_col;

		curr_row = curr->position[0] - 'A';
		curr_col = curr->position[1] - '1';
		arr[0] = (curr_row << 5) | (curr_col << 2);
		list_size++;

		curr = curr->next;
		if (curr != NULL)
		{
			curr_row = curr->position[0] - 'A';
			curr_col = curr->position[1] - '1';
			arr[0] = arr[0] | (curr_row >> 1);
			arr[1] = (curr_row << 7) | (curr_col << 4);
			list_size++;
		}
		else
		{
			arr[0] |= mask;
			fwrite(&arr, sizeof(BYTE), 1, bin_file);
			break;
		}

		curr = curr->next;
		if (curr != NULL)
		{
			curr_row = curr->position[0] - 'A';
			curr_col = curr->position[1] - '1';
			arr[1] = arr[1] | (curr_row << 1) | (curr_col >> 2);
			arr[2] = curr_col << 6;
			list_size++;
		}
		else
		{
			arr[1] |= mask;
			fwrite(&arr, sizeof(BYTE), 2, bin_file);
			break;
		}

		curr = curr->next;
		if (curr != NULL)
		{
			curr_row = curr->position[0] - 'A';
			curr_col = curr->position[1] - '1';
			arr[2] = arr[2] | (curr_row << 3) | (curr_col);
			list_size++;
		}
		else
		{
			arr[2] |= mask;
			fwrite(&arr, sizeof(BYTE), 3, bin_file);
			break;
		}

		fwrite(&arr, sizeof(BYTE), 3, bin_file);
		curr = curr->next;
	}
	fseek(bin_file, 0, SEEK_SET); /*Move the cursor to the beginning of the file to save the number of locations./*/
	fwrite(&list_size, sizeof(unsigned short int), 1, bin_file);
	fclose(bin_file);
}

/********* checkAndDisplayPathFromFile **********************
The function takes as input a name of a binary file containing positions and creates a list
of those positions.
If the created list does not contain a valid knight's path, then the function finishes
and returns 1. Otherwise - removes duplicates from the list and prints a table representing this path.
***************************************************/
int checkAndDisplayPathFromFile(char* file_name)
{
	FILE* bin_file = fopen(file_name, "rb");
	if (checkFile(bin_file) == false)
		return -1;

	chessPosList pathList;
	makeEmptyList(&pathList);

	short int list_size, updated_list_size;

	if (getListFromFile(bin_file, &pathList, &list_size) == false)
	{
		printf("Invalid knight's path!\n");
		return 1;
	}
	else
	{
		display(&pathList);
		updated_list_size = getCurrListSize(&pathList);
		if (pathCoveringAllBoard(updated_list_size) == true)
		{
			printf("Knight's path covering all board!\n");
			return 2;
		}
		else
		{
			printf("Knight's path not covering all board!\n");
			return 3;
		}
	}
}

/********* getListFromFile **********************
The function reads and creates a list of positions from the binary file.
Each time the function manages to read a location from the file it puts it in the list.
If the path obtained while reading the locations is invalid - the function finishes and returns a "false".
***************************************************/
bool getListFromFile(FILE* bin_file, chessPosList* lst, short int* psize)
{
	short int list_size;
	fread(&list_size, sizeof(short int), 1, bin_file);
	*psize = list_size;

	BYTE first, second, third, mask1 = 0x07;
	chessPos curr_position, tmp_position;
	int i, tmpSize, check;

	for (i = 0; i < list_size; i += 4)
	{
		tmpSize = 4, check = 0;  /*The "check" variable checks if the reading from the file was successful*/

		check = fread(&first, sizeof(BYTE), 1, bin_file);
		if (check)
		{
			tmp_position[0] = (first >> 5) + 'A';
			tmp_position[1] = (first >> 2 & mask1) + '1';
			if (i == 0 || validMove(curr_position, tmp_position) == true)
			{
				curr_position[0] = tmp_position[0];
				curr_position[1] = tmp_position[1];
				insertDataToEndList(lst, curr_position);
				tmpSize--;
				check = 0;
			}
			else
			{
				if (validMove(curr_position, tmp_position) == false)
					return false;
			}
		}

		check = fread(&second, sizeof(BYTE), 1, bin_file);
		if (check)
		{
			tmp_position[0] = ((first << 1 & mask1) | second >> 7) + 'A';
			tmp_position[1] = (second >> 4 & mask1) + '1';
			if (validMove(curr_position, tmp_position) == false)
				return false;
			else
			{
				curr_position[0] = tmp_position[0];
				curr_position[1] = tmp_position[1];
				insertDataToEndList(lst, curr_position);
				tmpSize--;
				check = 0;
			}
		}
		else
			return true;

		check = fread(&third, sizeof(BYTE), 1, bin_file);
		if (check)
		{
			tmp_position[0] = (second >> 1 & mask1) + 'A';
			tmp_position[1] = ((second << 2 & mask1) | third >> 6) + '1';
			if (validMove(curr_position, tmp_position) == false)
				return false;
			else
			{
				curr_position[0] = tmp_position[0];
				curr_position[1] = tmp_position[1];
				insertDataToEndList(lst, curr_position);
				tmpSize--;
				check = 0;
			}
		}
		else
			return true;

		if (tmpSize == 1)
		{
			tmp_position[0] = (third >> 3 & mask1) + 'A';
			tmp_position[1] = (third & mask1) + '1';
			if (validMove(curr_position, tmp_position) == false)
				return false;
			else
			{
				curr_position[0] = tmp_position[0];
				curr_position[1] = tmp_position[1];
				insertDataToEndList(lst, curr_position);
			}
		}
	}
}

/********* validMove **********************
The function receives as input a position and the next position after it in the list
and checks whether the move between the positions is valid.
***************************************************/
bool validMove(chessPos startingPosition, chessPos nextPosition)
{
	int row, col, nextrow, nextcol;
	row = startingPosition[0] + 'A';
	col = startingPosition[1] + '1';
	nextrow = nextPosition[0] + 'A';
	nextcol = nextPosition[1] + '1';

	if (row + 2 == nextrow || row - 2 == nextrow)
	{
		if (col + 1 == nextcol || col - 1 == nextcol)
			return true;
	}
	else if (col + 2 == nextcol || col - 2 == nextcol)
	{
		if (row + 1 == nextrow || row - 1 == nextrow)
			return true;
	}
	else
		return false;
}
