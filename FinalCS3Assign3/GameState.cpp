#include "GameState.h"

GameState::GameState()
{

	Board b;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			b.board[i][j] = 1;
		}
	}

	numMoves = 0;
	expectedMoves = 0;
	pathToWin = " ";
}

void GameState::print()
{
	cout << "Number of moves: " << this->getNumMoves()<<" ";
	cout << "Priority Number: " << this->getExpectedMoves()<<" ";
	cout << "Path: " << this->getPathToWin() << endl;
	Board b = this->getBoard();
	cout << b.toString() << endl << endl;
}

int GameState:: priorityNum(Board b)
{
	int checkArr[3][3];
	int sum = 0, check;
	int num = 0;
	for (int index = 0; index < 3; index++)
	{
		for (int j = 0; j < 3; j++)
		{
			num += 1;
			checkArr[index][j] = num;

		}
	}
	for (int i = 0; i < 3; i++)
	{
		check = 0;
		for (int j = 0; j < 3; j++)
		{

			if (b.board[i][j] == checkArr[i][j])sum += 0;
			else
			{
				for (int k = 0; k < 3; k++)
				{
					if (b.board[i][k] == checkArr[i][j] )
					{
						sum += 1;
						check++;
					}
					if (b.board[i][k] == checkArr[i][j])
					{
						sum += 1;
						check++;
					}
				}
				if (check == 0) sum += 2;
			}
		}
	} 
	return sum/=3;
}

GameState::~GameState()
{
}
