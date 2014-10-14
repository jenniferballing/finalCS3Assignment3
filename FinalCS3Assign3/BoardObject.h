/*Object that holds all printed information*/

#ifndef BOARDOBJECT_H
#define BOARDOBJECT_H
#include "Board.h"
#include <iostream>

using namespace std;

/*Class object that holds the Board, the Previous State, Current State, and Move Location*/
class BoardObject
{
	Board board; //Holds an instance of the Board class
	int currentState; //First state in the display
	int previousState; //Second state in the display or "from" state
	string location; //The description of the move location and direction

public:
	BoardObject();

	//getters and setters
	void setLocation(string s);
	void setBoard(Board);
	void setSequence(int);
	void setTier(int);
	Board getBoard(){ return board; }
	string getLocation() { return location; }
	int getSequence(){ return currentState; }
	int getTier(){ return previousState; }

	void printObj(); // Prints the object in the format given by the assignment
	~BoardObject();
};
#endif

