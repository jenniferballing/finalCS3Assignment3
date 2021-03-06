#include "Board.h"
#include "BoardObject.h"
#include "GameState.h"
#include "Queue.h"
#include "AvlTree.h"
#include "RotationGame.h"
Board inputBoards(int boardNumber);
void aStarGameLogic(AvlTree<GameState> &tree, GameState game);
GameState* aStarGetBoards(AvlTree<GameState> &tree, Board b);
int main()
{
	/***PART ONE***/

	AvlTree <int> tree;
	int arr[9] = { 1, 3, 5, 7, 9, 11, 2, 4, 8 };

	//Add: 1 3 5 7 9 11 2 4 8  (now print tree)
	for (int i = 0; i < 9; i++)
	{
		tree.insert(arr[i]);
	}
	cout << tree.toString() << endl;

	//Remove 7 9(now print tree)
	tree.remove(7);
	tree.remove(9);
	cout << tree.toString() << endl;

	//Add 50 30 15 18 (now print tree)
	int nArr[4] = { 50, 30, 15, 18 };
	for (int i = 0; i < 4; i++)
	{
		tree.insert(nArr[i]);
	}
	cout << tree.toString() << endl;

	//Remove Min(now print tree)
	tree.removeMin();
	cout << tree.toString() << endl;

	//Remove Min(now print tree)
	tree.removeMin();
	cout << tree.toString() << endl;

	//Remove Min(now print tree)
	tree.removeMin();
	cout << tree.toString() << endl;

	//Add 17(now print tree)
	tree.insert(17);
	cout << tree.toString() << endl;

	/*****************************/

	/*Board test1, test2, test3, test4; 
	int arr1[9] = { 9, 1, 2, 3, 4, 5, 6, 7, 8 };
	int arr2[9] = { 7, 5, 9, 1, 8, 3, 4, 2, 6 };
	int arr3[9] = { 9, 8, 6, 1, 2, 5, 4, 7, 3 };
	int arr4[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int num = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			test1.board[i][j] = arr1[num];
			test2.board[i][j] = arr2[num];
			test3.board[i][j] = arr3[num];
			test4.board[i][j] = arr4[num];
			num++;
		}
	}
	GameState g;
	cout << "Should be 4: " << endl<< g.priorityNum(test1) << endl;
	cout << "Should be 3: " << endl << g.priorityNum(test2) << endl;
	cout << "Should be 3: " << endl << g.priorityNum(test3) << endl;
	cout << "Should be 0: " << endl << g.priorityNum(test4) << endl;*/
	/***PART TWO***/
	//Instantiate the Rotation Game
	RotationGame rotGame;

	//Set the values of the board
	Board boardInput1;
	boardInput1 = inputBoards(1);

	//Set up for brute force method
	BoardObject boardObject;
	boardObject.setBoard(boardInput1);
	Queue myQueue;
	myQueue.Insert(boardObject);
	//rotGame.bruteForceSolve(myQueue, boardObject);

	//Set up for AVL method
	AvlTree<GameState> avlTree;
	GameState game;
	game.setBoard(boardInput1);
	int priority = game.priorityNum(boardInput1);
	game.setExpectedMoves(priority);
	avlTree.insert(game);
	rotGame.aStarSolve(avlTree, game);

	return 0;
}

Board inputBoards(int boardNumber)
{
	int arr[9];
	if (boardNumber == 1)
	{
		arr[0] = 5;
		arr[1] = 8;
		arr[2] = 6;
		arr[3] = 4;
		arr[4] = 3;
		arr[5] = 1;
		arr[6] = 9;
		arr[7] = 7;
		arr[8] = 2;

	}
	else if (boardNumber == 2)
	{
		arr[0] = 2;
		arr[1] = 1;
		arr[2] = 8;
		arr[3] = 9;
		arr[4] = 4;
		arr[5] = 7;
		arr[6] = 3;
		arr[7] = 6;
		arr[8] = 5;
	}
	else if (boardNumber == 3)
	{
		arr[0] = 4;
		arr[1] = 5;
		arr[2] = 6;
		arr[3] = 7;
		arr[4] = 8;
		arr[5] = 9;
		arr[6] = 1;
		arr[7] = 2;
		arr[8] = 3;
	}
	else if (boardNumber == 4)
	{
		Board b;
		int num = 0;
		b.makeBoard(2);
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				arr[num] = b.board[i][j];
				num++;
			}
		}
	}

	int number = 0;

	//Two dimentional array to set initial values in board
	Board board;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			board.board[i][j] = arr[number];
			number++;
		}
	}
	return board;
}

/*void aStarGameLogic(AvlTree<GameState> &tree, GameState game)
{
	//Goal Board
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
		//Find min based on expected moves
		GameState tempGame = tree.findMin();
		tempGame.print();

		//cout << "min: " << tempGame.getExpectedMoves() << endl;
		GameState *gameArr = aStarGetBoards(tree, tempGame.getBoard());

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
	GameState arr[12];
	//GameState *arr = new GameState[12];
	int num = 0;

	for (int i = 0; i < 3; i++)
	{
		temp.rotateNorth(i);
		arr[num].setBoard(temp);
		arr[num].setExpectedMoves(game.priorityNum(temp));
		arr[num].setPathToWin("=>North Col " + to_string(i));
		temp = b;
		num++;

		temp.rotateSouth(i);
		arr[num].setBoard(temp);
		arr[num].setExpectedMoves(game.priorityNum(temp));
		arr[num].setPathToWin("=>South Col " + to_string(i));
		temp = b;
		num++;

		temp.rotateEast(i);
		arr[num].setBoard(temp);
		arr[num].setExpectedMoves(game.priorityNum(temp));
		arr[num].setPathToWin("=>East Row " + to_string(i));
		temp = b;
		num++;

		temp.rotateWest(i);
		arr[num].setBoard(temp);
		arr[num].setExpectedMoves(game.priorityNum(temp));
		arr[num].setPathToWin("=>West Row " + to_string(i));
		temp = b;
		num++;
	}
	GameState *ptr = arr;
	return ptr;
	//return arr;
}*/
