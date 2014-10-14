#include "BoardObject.h"

//Set everything to starting point
BoardObject::BoardObject()
{
	Board b;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			b.board[i][j] = 0;
		}
	}
	currentState = 0;
	previousState = -1;
	location = " ";
}

//getters and setters
void BoardObject::setBoard(Board b)
{
	board = b;
}

void BoardObject::setSequence(int s)
{
	currentState = s;
}

void BoardObject::setTier(int t)
{
	previousState = t;
}

void BoardObject::setLocation(string l)
{
	location = l;
}

//Print the object in the desired format
void BoardObject::printObj()
{
	cout << "State " << currentState << " " << "From State " << previousState << " " << location << endl;
	cout << board.toString() << endl;
}

BoardObject::~BoardObject()
{
}
