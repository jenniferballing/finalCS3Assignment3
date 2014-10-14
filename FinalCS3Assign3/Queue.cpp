#include "Queue.h"

//Initialize values to starting values
QueueNode::QueueNode()
{
	Board gameBoard;//board with initial values
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			gameBoard.board[i][j] = 0;
		}
	}
	boardObj.setBoard(gameBoard);
	boardObj.setLocation(" ");
	boardObj.setSequence(0);
	boardObj.setTier(0);

	next = NULL;
}

Queue::Queue()
{
	head = NULL;
}

//Insert BoardObjects oon the end of the list
void Queue::Insert(BoardObject o)
{
	//create new node to insert
	QueueNode* newNode = new QueueNode();
	//set the BoardObject of the node
	newNode->boardObj = o;
	//set the pointer
	newNode->next = NULL;

	//check for an empty list
	if (head == NULL)
	{
		head = newNode;
	}
	//Find the end of the list and insert the new node there
	else
	{
		QueueNode *temp = head;
		//Check to see if this value of temp is the last node of the list
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		//set the new node as the last value in the list
		temp->next = newNode;
	}
}

//Delete the new node from the list and from memory
void Queue::Delete()
{
	QueueNode* deletedNode = head;
	head = head->next;
	//Let me memory go
	delete deletedNode;
}
