#include "RotationGame.h"

GameState* aStarGetBoards(AvlTree<GameState> &tree, Board b);
BoardObject* returnBoards(Queue myQueue, Board b);

RotationGame::RotationGame()
{
}

void RotationGame::bruteForceSolve(Queue myQueue, BoardObject b)
{
	//Goal board
	Board winningBoard;
	int count = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			winningBoard.board[i][j] = count;
			count++;
		}
	}

	int currentState = 1;
	int prevState = 0;
	int num = 0;

	bool win = false;
	int prev = 0;
	while (!win)
	{
		//get first obj
		BoardObject parentObj;
		parentObj = myQueue.head->boardObj;
		Board parentBoard = parentObj.getBoard();

		//delete it from queue
		myQueue.Delete();

		//Get the rotations
		BoardObject *boardObjArr = returnBoards(myQueue, parentBoard);
		if (!win)
		{
			for (int i = 0; i < 12; i++)
			{
				BoardObject childObj;

				Board childBoard = boardObjArr[i].getBoard();
				childObj.setBoard(childBoard);

				childObj.setTier(prev);
				childObj.setSequence(currentState);

				string prevLocation = parentObj.getLocation();
				string currentMove = boardObjArr[i].getLocation();

				childObj.setLocation(currentMove + " " + prevLocation);
				myQueue.Insert(childObj);


				if (childBoard == winningBoard)
				{
					childObj.printObj();
					cout << "YOU WIN!! Original Board" << endl;
					Board winningB = b.getBoard();
					cout << winningB.toString();

					win = true;
					return;
				}
				else
				{
					childObj.printObj();
				}

				currentState++;
			}prev++;
		}
	}
}

BoardObject* returnBoards(Queue myQueue, Board b)
{
	Board temp;
	temp = b;
	BoardObject *arr = new BoardObject[12];//BoardObject *arr = new BoardObject[12];
	int num = 0;

	for (int i = 0; i < 3; i++)
	{
		temp.rotateNorth(i);
		arr[num].setBoard(temp);
		arr[num].setLocation("=>North Col " + to_string(i));
		temp = b;
		num++;

		temp.rotateSouth(i);
		arr[num].setBoard(temp);
		arr[num].setLocation("=>South Col " + to_string(i));
		temp = b;
		num++;

		temp.rotateEast(i);
		arr[num].setBoard(temp);
		arr[num].setLocation("=>East Row " + to_string(i));
		temp = b;
		num++;

		temp.rotateWest(i);
		arr[num].setBoard(temp);
		arr[num].setLocation("=>West Row " + to_string(i));
		temp = b;
		num++;
	}
	return arr;
}
void RotationGame::aStarSolve(AvlTree<GameState> tree, GameState game)
{		//Goal Board
	Board winningBoard;
	int count = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			winningBoard.board[i][j] = count;
			count++;
		}
	}

	bool win = false;
	while (!win)
	{
		Board b;
		int num = 1;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				b.board[i][j] = num;
				num++;
			}
		}
		GameState *gameArr = aStarGetBoards(tree, b);
		//Find min based on expected moves
		GameState tempGame = tree.findMin();
		tempGame.print();

		//cout << "min: " << tempGame.getExpectedMoves() << endl;
		//GameState *gameArr = aStarGetBoards(tree, tempGame.getBoard());

		//insert 12 rotated boards to avl queue
		for (int i = 0; i < 12; i++)
		{
			tree.insert(gameArr[i]);
			//cout << "i: " << i << "Expected Moves: " << gameArr[i].getExpectedMoves() << endl;
		}
		if (tempGame.getBoard() == winningBoard)
		{
			tempGame.print();
			cout << "YOU WIN!! Original Board" << endl;
			cout << winningBoard.toString();
			win = true;
		}
	}
}
GameState* aStarGetBoards(AvlTree<GameState> &tree, Board b)
{
	Board temp = b;
	GameState game;
	//GameState arr[12];
	GameState *arr[12];
	for (int i = 0; i < 12; i++)
	{
		arr[i] = new GameState();
	}
	int num = 0;

	for (int i = 0; i < 3; i++)
	{
		temp.rotateNorth(i);
		arr[num]->setBoard(temp);
		arr[num]->setExpectedMoves(game.priorityNum(temp));
		arr[num]->setPathToWin("=>North Col " + to_string(i));
		temp = b;
		num++;

		temp.rotateSouth(i);
		arr[num]->setBoard(temp);
		arr[num]->setExpectedMoves(game.priorityNum(temp));
		arr[num]->setPathToWin("=>South Col " + to_string(i));
		temp = b;
		num++;

		temp.rotateEast(i);
		arr[num]->setBoard(temp);
		arr[num]->setExpectedMoves(game.priorityNum(temp));
		arr[num]->setPathToWin("=>East Row " + to_string(i));
		temp = b;
		num++;

		temp.rotateWest(i);
		arr[num]->setBoard(temp);
		arr[num]->setExpectedMoves(game.priorityNum(temp));
		arr[num]->setPathToWin("=>West Row " + to_string(i));
		temp = b;
		num++;
	}
	return *arr;
}


RotationGame::~RotationGame()
{
}
