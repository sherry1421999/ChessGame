#include "Project - Lists.h"

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

/******************************************** insertTreeNodeToStartLst *******************************************
The function insert node to start child list.
******************************************************************************************************************/
void insertTreeNodeToStartLst(treeNodeListCell* lst, treeNodeListCell* newLnode)
{
	treeNodeListCell* saver;

	saver = lst;
	lst = newLnode;
	newLnode->next = saver;
}

/******************************************** insertDataToStartChildList *****************************************************
The function insert data to start child list.
******************************************************************************************************************/
treeNodeListCell* insertDataToStartChildList(treeNodeListCell* Lnode, treeNode* Tnode)
{
	treeNodeListCell* newLcell = createNewListCell(Tnode, NULL);
	insertTreeNodeToStartLst(Lnode, newLcell);

	return newLcell;
}

/******************************************** createNewListCell *******************************************
The function creates new list cell node.
***********************************************************************************************************/
treeNodeListCell* createNewListCell(treeNode* Tnode, treeNodeListCell* next)
{
	treeNodeListCell* res;

	res = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	checkMemoryAllocation(res);

	res->node = Tnode;
	res->next = next;

	return res;
}

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
	if (maxPathLen == pow(ROWS,2))
	{
		printf("found knight path that covering all board!\n");
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

/******************************************** insertDataToEndList **********************************************************
The function insert data to the end of the list.
**************************************************************************************************************************************/
void insertDataToEndList(chessPosList* lst, chessPos position)
{
	chessPosCell* newLnode = createNewListNode(position, NULL);
	insertNodeToEndList(lst, newLnode);
}

/******************************************** insertNodeToEndList **********************************************************
The function insert new node to the end of the list.
**************************************************************************************************************************************/
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

/********* getCurrListSize **********************
The function receives a list as input and returns its size.
***************************************************/
int getCurrListSize(chessPosList* lst)
{
	chessPosCell* curr = lst->head;
	int count = 0;

	while (curr)
	{
		count++;
		curr = curr->next;
	}

	return count;
}

/********* pathCoveringAllBoard **********************
The function is received as an input a list size (after duplicates have been removed
from the list). If this size is the same as the number of cells in the board - the path covers the entire board.
***************************************************/
bool pathCoveringAllBoard(int listSize)
{
	if (listSize == pow(ROWS, 2))
		return true;
	else
		return false;
}

/*for us to check.*/
void printList(chessPosList* lst)
{
	chessPosCell* curr = lst->head;
	while (curr)
	{
		printf("%c%c ", curr->position[0], curr->position[1]);
		curr = curr->next;
	}
}