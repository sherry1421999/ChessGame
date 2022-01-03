#include "Project - Q4.h"

/******************************************** findKnightPathCoveringAllBoard **********************************************************
The function finds a route that covers all the squares of the board starting from the tree root obtained as a parameter.
The route will be represented as a linked list whose first cell will contain the location at the root of the route tree and the other 
locations in the list will be the next cells in the route in order.
If there is no path that passes through all the slots in the board, the function will return NULL. 
**************************************************************************************************************************************/
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree)
{
	chessPosList* maxLst = NULL;
	int maxPathLen;

	maxLst = findKnightPathCoveringAllBoardHelper(path_tree->root, &maxPathLen);
	if (maxPathLen == 25)
	{
		printf("found knight path that covering all board!");
		return maxLst;
	}
	else
	{
		freeLst(maxLst);
		return NULL;
	}
}

/******************************************** findKnightPathCoveringAllBoard **********************************************************
The function finds a route that covers all the squares of the board starting from the trajectory tree root obtained as a parameter in recurtion.
The route will be represented as a linked list whose first cell will contain the location at the root of the route tree and the other
locations in the list will be the next cells in the route in order.
If there is no path that passes through all the slots in the board, the function will return NULL.
**************************************************************************************************************************************/
chessPosCell* findKnightPathCoveringAllBoardHelper(treeNode* root, int* psize)
{
	chessPosList* currLst, * maxLst;
	treeNodeListCell* currTnode;
	int currLen = 0, maxLen = 0;

	currLst = (chessPosList*)malloc(sizeof(chessPosList));
	checkMemoryAllocation(currLst);
	makeEmptyList(currLst);

	maxLst = (chessPosList*)malloc(sizeof(chessPosList));
	checkMemoryAllocation(maxLst);
	makeEmptyList(maxLst);

	if (root == NULL)
	{
		*psize = ERROR;
		return NULL;
	}

	else if (root->next_possible_position == NULL)
	{
		insertDataToStartList(currLst, root->position);
		*psize = 1;
		return currLst;
	}
	else
	{
		currTnode = root->next_possible_position;

		while (currTnode)
		{
			currLst = findKnightPathCoveringAllBoardHelper(currTnode->node, &currLen);
			if (maxLen < currLen)
			{
				maxLen = currLen;
				if (maxLst)
					freeLst(maxLst);
				maxLst = currLst;
			}
			else
				freeLst(currLst);

			currTnode = currTnode->next;
		}

		insertDataToStartList(maxLst, root->position);
		*psize = maxLen + 1;
		return maxLst;
	}
}
/******************************************** insertDataToStartList **********************************************************
The function inserts data to the start of the List.
**************************************************************************************************************************************/
void insertDataToStartList(chessPosList* lst, chessPos position)
{
	chessPosCell* newLnode = createNewListNode(position, NULL);
	insertNodeToStartList(lst, newLnode);
}
/******************************************** createNewListNode **********************************************************
The function creates new ListNode.
**************************************************************************************************************************************/
chessPosCell* createNewListNode(chessPos position, chessPosCell* next)
{
	chessPosCell* newLnode = (chessPosCell*)malloc(sizeof(chessPosCell));
	checkMemoryAllocation(newLnode);

	newLnode->position[0] = position[0];
	newLnode->position[1] = position[1];
	newLnode->next = next;

	return newLnode;
}
/******************************************** insertNodeToStartList **********************************************************
The function insert Node To the Start of the List .
**************************************************************************************************************************************/
void insertNodeToStartList(chessPosList* lst, chessPosCell* newLnode)
{
	if (isEmptyList(*lst))
		lst->head = lst->tail = newLnode;
	else
	{
		newLnode->next = lst->head;
		lst->head = newLnode;
	}
}
/******************************************** isEmptyList **********************************************************
The function checks if the list is empty.
**************************************************************************************************************************************/
bool isEmptyList(chessPosList lst)
{
	return (lst.head == NULL);
}
/******************************************** makeEmptyList **********************************************************
The function makes a new list.
**************************************************************************************************************************************/
void makeEmptyList(chessPosList* lst)
{
	lst->head = lst->tail = NULL;
}
/******************************************** freeLst **********************************************************
The function free the list.
**************************************************************************************************************************************/
void freeLst(chessPosList* lst)
{
	chessPosCell* curr = lst->head, * next;

	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
}
