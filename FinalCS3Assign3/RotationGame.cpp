#include "RotationGame.h"
#include <vector>

GameState* aStarGetBoards(AvlTree<GameState> &tree, Board b);
Board* aStarIntBoards(AvlTree<int> &tree, Board b);
BoardObject* returnBoards(Queue myQueue, Board b);
bool duplicates(Board a, Board b);

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
void RotationGame::aStarSolve(AvlTree<GameState> &tree, GameState &game)
{	//Goal Board
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

	GameState *gameArr;
	
	bool win = false;
	vector<Board> boardArr(0);
	while (!win)
	{
		
		//Find min based on expected moves
		GameState g;
		
		int num = 0;
		
		GameState minGame = tree.findMin();
		minGame.print();
		bool dup = false;
		for (auto st : boardArr)
		{
			if (duplicates(st, minGame.getBoard()))
			{
				dup = true;
				break;
			}
		}
		if (!dup)
		{
			boardArr.push_back(minGame.getBoard());
		}
		tree.removeMin(g);

		
		gameArr = aStarGetBoards(tree, minGame.getBoard());
		bool duplicate=false;
		int removeNum=-1;
		for (int i = 0; i < 12; i++)
		{			
			for (int j = 0; j <boardArr.size(); j++)
			{
				Board b = gameArr[i].getBoard();
				Board a = boardArr[j];
				duplicate = duplicates(a, b);
				if (duplicate)
				{
					removeNum = i;
				}
			}
			if (removeNum < 0)
			{
				tree.insert(gameArr[i]);
				removeNum = -1;
			}
			else
			{
				removeNum = -1;
			}
		}

		if (minGame.getBoard() == winningBoard)
		{
			minGame.print();
			cout << "YOU WIN!! Original Board" << endl;
			cout << winningBoard.toString();
			win = true;
		}
	}
}
bool duplicates(Board a, Board b)
{
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			if (a.board[i][j] == b.board[i][j]) count++;
		}
	}
	if (count == 9)
	{
		return true;
	}
	return false;
}
/*void RotationGame::aStarWithInts(AvlTree<int> &tree, Board b)
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

	GameState *gameArr;

	gameArr = aStarGetBoards(tree, b);
	bool win = false;
	while (!win)
	{
		//Find min based on expected moves
		GameState g;
		GameState tempGame = tree.findMin();
		tempGame.print();
		tree.removeMin(g);
		if (!tree.isEmpty())
		{
			tempGame = tree.findMin();
			tempGame.print();
		}



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

Board* aStarIntBoards(AvlTree<int> &tree, Board b)
{
	Board temp = b;
	int game;
	//GameState arr[12];
	Board *arr = new Board[12];
	//for (int i = 0; i < 12; i++)
	//{
	//	arr[i] = new GameState();
	//}
	int num = 0;

	for (int i = 0; i < 3; i++)
	{

		temp.rotateNorth(i);
		arr[num] = temp;
		temp = b;
		num++;

		temp.rotateSouth(i);
		arr[num] = temp;
		temp = b;
		num++;

		temp.rotateEast(i);
		arr[num] = temp;
		temp = b;
		num++;

		temp.rotateWest(i);
		arr[num] = temp;
		temp = b;
		num++;
	}
	return arr;

}*/
GameState* aStarGetBoards(AvlTree<GameState> &tree, Board b)
{
	Board temp = b;
	
	GameState game;
	
	GameState *arr = new GameState[12];

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
	return arr;
}


RotationGame::~RotationGame()
{
}
