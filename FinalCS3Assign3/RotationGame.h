#ifndef ROTATIONGAME_H
#define ROTATIONGAME_H
#include "GameState.h"
#include "BoardObject.h"
#include "Queue.h"
#include "AvlTree.h"

class RotationGame
{
	GameState gameState;
	BoardObject boardObject;

public:
	RotationGame();
	void bruteForceSolve(Queue myQueue, BoardObject b);
	void aStarSolve(AvlTree<GameState> &tree, GameState &game);
	void aStarWithInts(AvlTree<int> &tree, Board b);
	~RotationGame();
};
#endif
