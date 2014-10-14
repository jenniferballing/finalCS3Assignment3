#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Board.h"
#include "AvlTree.h"

using namespace std;
class GameState
{
	Board board;
	int numMoves;
	int expectedMoves;
	string pathToWin;

public:
	GameState();
	~GameState();

	Board getBoard(){ return board; }
	int getNumMoves(){ return numMoves; }
	int getExpectedMoves(){ return expectedMoves; }
	string getPathToWin(){ return pathToWin; }

	
	void setBoard(Board b){ board = b; }
	void setNumMoves(int n){ numMoves = n; }
	void setExpectedMoves(int e){ expectedMoves = e; }
	void setPathToWin(string s){ pathToWin = s; }

	int priorityNum(Board);
	void print();


	//friend ostream&  operator<<(ostream& ss, const GameState& gs);
};

/*stream&  operator<<(ostream& ss, const GameState& gs) {
	ss << gs.toString() << endl;
	return ss;
}*/

#endif
