#include "Project - Q3.h"

/******************************************** findAllPossibleKnightPaths ********************************************
This function finds All Possible Knight Paths.
*********************************************************************************************************************/
pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
	pathTree tree;
	chessPosArray*** validPosArray;
	bool path[ROWS][COLS];

	initializePathTable(path);
	validPosArray = ValidKnightMoves();
	tree.root = findAllPossibleKnightPathshelper(startingPosition, validPosArray, path);
	printf("The tree was created!\n");
	return tree;
}
/******************************************** findAllPossibleKnightPaths *****************************************************
The function builds a tree with all possible differential paths which start with a square obtained as a parameter.
At each node X the function searches for all possible nodes to which the difference can continue while avoiding walking in circles.
All possible continuation nodes will be saved in the list and stored in the list at the X node.
If it is not possible to continue to any node from X then X is at the end of one of the tracks which started at the root and 
it will be a leaf in the returned tree.
******************************************************************************************************************************/
treeNode* findAllPossibleKnightPathshelper(chessPos* startingPosition, chessPosArray*** mat, bool path[][COLS])
{
	int row, col, size, curr_row, curr_col, i;
	treeNode* root, * child;
	chessPosArray* possibleMovesArr;
	chessPos* childPosition;

	row = startingPosition[0][0] - 'A';
	col = startingPosition[0][1] - '1';

	possibleMovesArr = mat[row][col];
	size = possibleMovesArr->size;
	root = createNewTreeNode(startingPosition);

	if (checkIfAllTrue(possibleMovesArr, size, path) == true)
		return root;

	else
	{
		path[row][col] = true;
		
		for (i = 0; i < size; i++)
		{
			childPosition = possibleMovesArr->positions[i];
			curr_row = childPosition[0][0] - 'A';
			curr_col = childPosition[0][1] - '1';

			if (path[curr_row][curr_col] == false)
			{
				child = findAllPossibleKnightPathshelper(childPosition, mat, path);
				root->next_possible_position = insertDataToStartChildList(root->next_possible_position, child);
			}
		}
	}
	path[row][col] = false;
	return root;
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

/******************************************** createNewTreeNode *****************************************************
The function creates new tree node.
******************************************************************************************************************/
treeNode* createNewTreeNode(chessPos* startingPosition)
{
	treeNode* newTnode = (treeNode*)malloc(sizeof(treeNode));
	checkMemoryAllocation(newTnode);

	newTnode->position[0] = startingPosition[0][0];
	newTnode->position[1] = startingPosition[0][1];
	newTnode->next_possible_position = NULL;

	return newTnode;
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

/******************************************** createNewListCell *******************************************
The function prints the tree. (for us to check)
******************************************************************************************************************/
void printPathTree(pathTree tr)
{
	printPathTreeRec(tr.root, 1);
}
/******************************************** printPathTreeRec *******************************************
The function prints the tree. (for us to check)
******************************************************************************************************************/
void printPathTreeRec(treeNode* root, int level)
{
	treeNodeListCell* cur_node;
	if (root == NULL)
		return;
	else
	{
		cur_node = root->next_possible_position;
		printf("[LEVEL %d] Possible moves from %c%c: [", level, root->position[0], root->position[1]);
		while (cur_node != NULL)
		{
			printf("%c%c", cur_node->node->position[0], cur_node->node->position[1]);
			if (cur_node->next != NULL)
				printf(", ");

			cur_node = cur_node->next;
		}
		printf("]\n");

		cur_node = root->next_possible_position;
		while (cur_node != NULL)
		{
			printPathTreeRec(cur_node->node, level + 1);
			cur_node = cur_node->next;
			if (cur_node != NULL)
				printf("\nNEXT CHILD OF (%c%c) - LEVEL %d\n", root->position[0], root->position[1], level);
		}
	}
}