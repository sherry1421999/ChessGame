#include "Project - Q5.h"

void saveListToBinFile(char* file_name, chessPosList* pos_list)
{
	unsigned short int list_size = 0;
	/*getListSize(pos_list, &list_size);*/
	FILE* bin_file = fopen(file_name, "wb");
	checkFile(bin_file);
	fseek(bin_file, sizeof(unsigned short int), SEEK_SET);
	/*fwrite(&list_size, sizeof(unsigned short int), 1, bin_file);*/

	chessPosCell* curr = pos_list->head;

	while(curr)
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
			arr[2] = arr[2] | (curr_row << 3) | (curr_col << 3);
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
	fseek(bin_file,0,SEEK_SET);
	fwrite(&list_size, sizeof(unsigned short int), 1, bin_file);
	fclose(bin_file);
}

//void writeOneByteToFile(chessPosCell* curr, FILE* file)
//{
//	BYTE arr[1], mask = 0x00;
//	int curr_row, curr_col;
//	curr_row = curr->position[0] - 'A';
//	curr_col = curr->position[1] - '1';
//	arr[0] = ((curr_row << 5) | (curr_col << 2)) | mask;
//
//	fwrite(&arr, sizeof(BYTE), 1, file);
//}
//
//void writeTwoBytesToFile(chessPosCell* curr, FILE* file)
//{
//	BYTE arr[2], mask= 0x00;
//	int curr_row, curr_col;
//
//	curr_row = curr->position[0] - 'A';
//	curr_col = curr->position[1] - '1';
//	arr[0] = (curr_row << 5) | (curr_col << 2);
//
//	curr = curr->next;
//	curr_row = curr->position[0] - 'A';
//	curr_col = curr->position[1] - '1';
//	arr[0] = arr[0] | (curr_row >> 1);
//	arr[1] = ((curr_row << 7) | (curr_col << 4)) | mask;
//
//	fwrite(&arr, sizeof(BYTE), 1, file);
//}
//
//void writeThreeBytesToFile(chessPosCell* curr, FILE* bin_file)
//{
//	BYTE arr[3], mask = 0x00;
//	int curr_row, curr_col;
//
//	curr_row = curr->position[0] - 'A';
//	curr_col = curr->position[1] - '1';
//	arr[0] = (curr_row << 5) | (curr_col << 2);
//
//	curr = curr->next;
//	curr_row = curr->position[0] - 'A';
//	curr_col = curr->position[1] - '1';
//	arr[0] = arr[0] | (curr_row >> 1);
//	arr[1] = (curr_row << 7) | (curr_col << 4);
//
//	curr = curr->next;
//	curr_row = curr->position[0] - 'A';
//	curr_col = curr->position[1] - '1';
//	arr[1] = arr[1] | (curr_row << 1) | (curr_col >> 2);
//	arr[2] = curr_col << 6 | mask;
//
//	fwrite(&arr, sizeof(BYTE), 3, bin_file);
//}

//void writeFourBytesToFile(chessPosCell* curr, FILE* bin_file)
//{
//	BYTE arr[3], mask=0x00;
//	int curr_row, curr_col;
//
//	curr_row = curr->position[0] - 'A';
//	curr_col = curr->position[1] - '1';
//	arr[0] = (curr_row << 5) | (curr_col << 2);
//
//	curr = curr->next;
//	if (curr != NULL)
//	{
//		curr_row = curr->position[0] - 'A';
//		curr_col = curr->position[1] - '1';
//		arr[0] = arr[0] | (curr_row >> 1);
//		arr[1] = (curr_row << 7) | (curr_col << 4);
//	}
//	else
//	{
//		arr[0] |= mask;
//		fwrite(&arr, sizeof(BYTE), 1, bin_file);
//		return;
//	}
//
//	curr = curr->next;
//	if (curr != NULL)
//	{
//		curr_row = curr->position[0] - 'A';
//		curr_col = curr->position[1] - '1';
//		arr[1] = arr[1] | (curr_row << 1) | (curr_col >> 2);
//		arr[2] = curr_col << 6;
//	}
//	else
//	{
//		arr[1] |= mask;
//		fwrite(&arr, sizeof(BYTE), 2, bin_file);
//		return;
//	}
//
//	curr = curr->next;
//	if (curr != NULL)
//	{
//		curr_row = curr->position[0] - 'A';
//		curr_col = curr->position[1] - '1';
//		arr[2] = arr[2] | (curr_row << 3) | (curr_col << 3);
//	}
//	else
//	{
//		arr[2] |= mask;
//		fwrite(&arr, sizeof(BYTE), 3, bin_file);
//		return;
//	}
//
//	fwrite(&arr, sizeof(BYTE), 3, bin_file);	
//}

//void getListSize(chessPosList* pos_list, unsigned short int* psize)
//{
//	chessPosCell* curr = pos_list->head;
//
//	while (curr)
//	{
//		(*psize)++;
//		curr = curr->next;
//	}
//}

void checkFile(FILE* f)
{
	if (f == NULL)
	{
		printf("Opening file failed!\n");
		exit(-1);
	}
}