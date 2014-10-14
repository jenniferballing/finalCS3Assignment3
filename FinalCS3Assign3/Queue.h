/*Linked list which behaves like a queue*/
#ifndef QUEUE_H
#define QUEUE_H
#include <string>
#include <iostream>
#include "Board.h"
#include "BoardObject.h"


using namespace std;

//Declaration of the node for the list
//Node holds a BoardObject and a pointer to the 
//next node
struct QueueNode
{
public:
	BoardObject boardObj;//includes board, previous state, current state, and location
	QueueNode *next;

	QueueNode();
};

class Queue
{
public:
	QueueNode *head; //The first node in the list
	Queue();
	void Insert(BoardObject); //Insert object onto the end of the list
	void Delete();
};

#endif