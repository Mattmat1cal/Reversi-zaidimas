#include "GameLogic.h"
#include <iostream>
#include <vector>
Board& GameLogic::getGameBoard() { return this->gameBoard; }
Player& GameLogic::getLightPlayer() { return this->playerLight; }
Player& GameLogic::getDarkPlayer() { return this->playerDark; }
bool GameLogic::isLightPlayerTurn() { return (moveCounter % 2 == 0); }
void GameLogic::resetGame()
{
	moveCounter = 1;
	pieceCounter = 4;
	stalemateCounter = 0;
	gameBoard.resetBoard();
}
bool GameLogic::processMove(std::string inputCoordinates, std::vector<std::pair<int,int>> legalMoves)
{
	std::pair<int, int> coordinates;
	char currentPiece, opponentPiece;
	setCurrentAndOpponentPieces(currentPiece, opponentPiece);
	parseCoordinates(inputCoordinates, coordinates);
	if (std::find(legalMoves.begin(), legalMoves.end(), coordinates) != legalMoves.end())
	{
		gameBoard.setBoardTile(currentPiece, coordinates.first, coordinates.second);
		if (gameBoard.getBoardTile(coordinates.first, coordinates.second - 1) == opponentPiece) captureLeft(coordinates.first, coordinates.second, currentPiece, opponentPiece);
		if (gameBoard.getBoardTile(coordinates.first, coordinates.second + 1) == opponentPiece) captureRight(coordinates.first, coordinates.second, currentPiece, opponentPiece);
		if (gameBoard.getBoardTile(coordinates.first + 1, coordinates.second) == opponentPiece) captureDown(coordinates.first, coordinates.second, currentPiece, opponentPiece);
		if (gameBoard.getBoardTile(coordinates.first - 1, coordinates.second) == opponentPiece) captureUp(coordinates.first, coordinates.second, currentPiece, opponentPiece);
		if (gameBoard.getBoardTile(coordinates.first - 1, coordinates.second - 1) == opponentPiece) captureUpLeft(coordinates.first, coordinates.second, currentPiece, opponentPiece);
		if (gameBoard.getBoardTile(coordinates.first - 1, coordinates.second + 1) == opponentPiece) captureUpRight(coordinates.first, coordinates.second, currentPiece, opponentPiece);
		if (gameBoard.getBoardTile(coordinates.first + 1, coordinates.second - 1) == opponentPiece) captureDownLeft(coordinates.first, coordinates.second, currentPiece, opponentPiece);
		if (gameBoard.getBoardTile(coordinates.first + 1, coordinates.second + 1) == opponentPiece) captureDownRight(coordinates.first, coordinates.second, currentPiece, opponentPiece);
		moveCounter++;
		pieceCounter++;
		stalemateCounter = 0;
		return true;
	}
	else return false;
}
void GameLogic::parseCoordinates(std::string coordinates, std::pair<int,int>& parsedCoordinates)
{
	parsedCoordinates.second = coordinates.at(0) - 'a';
	parsedCoordinates.first = coordinates.at(1) - '1';
}
std::vector<std::pair<int, int>> GameLogic::getLegalMoves()
{
	std::vector<std::pair<int, int>> legalMoveVector;
	char currentPiece, opponentPiece;
	setCurrentAndOpponentPieces(currentPiece, opponentPiece);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (gameBoard.getBoardTile(i, j) == currentPiece)
			{
				checkColumn(legalMoveVector, i, j, currentPiece, opponentPiece);
				checkRow(legalMoveVector, i, j, currentPiece, opponentPiece);
				checkDiagonals(legalMoveVector, i, j, currentPiece, opponentPiece);
			}
		}
	}
	return legalMoveVector;
}
void GameLogic::checkRow(std::vector<std::pair<int, int>> &legalMoves, int rowNum, int columnNum, char currentPiece, char opponentPiece)
{
	if (columnNum < 7 && gameBoard.getBoardTile(rowNum, columnNum + 1) == opponentPiece)
	{
		for (int i = columnNum + 2; i < 8; i++)
		{
			if (gameBoard.getBoardTile(rowNum, i) == ' ')
			{
				legalMoves.push_back(std::make_pair(rowNum, i));
				break;
			}
			else if (gameBoard.getBoardTile(rowNum, i) == currentPiece) break;
		}
	}
	if (columnNum > 0 && gameBoard.getBoardTile(rowNum, columnNum - 1) == opponentPiece)
	{
		for (int i = columnNum - 2; i >= 0; i--)
		{
			if (gameBoard.getBoardTile(rowNum, i) == ' ')
			{
				legalMoves.push_back(std::make_pair(rowNum, i));
				break;
			}
			else if (gameBoard.getBoardTile(rowNum, i) == currentPiece) break;
		}
	}
}
void GameLogic::checkColumn(std::vector<std::pair<int, int>>& legalMoves, int rowNum, int columnNum, char currentPiece, char opponentPiece)
{
	if (rowNum < 7 && gameBoard.getBoardTile(rowNum + 1, columnNum) == opponentPiece)
	{
		for (int i = rowNum + 2; i < 8; i++)
		{
			if (gameBoard.getBoardTile(i, columnNum) == ' ')
			{
				legalMoves.push_back(std::make_pair(i, columnNum));
				break;
			}
			else if (gameBoard.getBoardTile(i, columnNum) == currentPiece) break;
		}
	}
	if (rowNum > 0 && gameBoard.getBoardTile(rowNum - 1, columnNum) == opponentPiece)
	{
		for (int i = rowNum - 2; i >= 0; i--)
		{
			if (gameBoard.getBoardTile(i, columnNum) == ' ')
			{
				legalMoves.push_back(std::make_pair(i, columnNum));
				break;
			}
			else if (gameBoard.getBoardTile(i, columnNum) == currentPiece) break;
		}
	}
}
void GameLogic::checkDiagonals(std::vector<std::pair<int,int>> &legalMoves, int rowNum, int columnNum, char currentPiece, char opponentPiece)
{
	if (rowNum < 7 && columnNum < 7 && gameBoard.getBoardTile(rowNum + 1, columnNum + 1) == opponentPiece)
	{
		for (int i = rowNum + 2, j = columnNum + 2; i < 8 && j < 8; i++, j++)
		{
			if (gameBoard.getBoardTile(i, j) == ' ')
			{
				legalMoves.push_back(std::make_pair(i, j));
				break;
			}
			else if (gameBoard.getBoardTile(i, j) == currentPiece) break;
		}
	}
	if (rowNum < 7 && columnNum > 0 && gameBoard.getBoardTile(rowNum + 1, columnNum - 1) == opponentPiece)
	{
		for (int i = rowNum + 2, j = columnNum - 2; i < 8 && j >= 0; i++, j--)
		{
			if (gameBoard.getBoardTile(i, j) == ' ')
			{
				legalMoves.push_back(std::make_pair(i, j));
				break;
			}
			else if (gameBoard.getBoardTile(i, j) == currentPiece) break;
		}
	}
	if (rowNum > 0 && columnNum < 7 && gameBoard.getBoardTile(rowNum - 1, columnNum + 1) == opponentPiece)
	{
		for (int i = rowNum - 2, j = columnNum + 2; i >= 0 && j < 8; i--, j++)
		{
			if (gameBoard.getBoardTile(i, j) == ' ')
			{
				legalMoves.push_back(std::make_pair(i, j));
				break;
			}
			else if (gameBoard.getBoardTile(i, j) == currentPiece) break;
		}
	}
	if (rowNum > 0 && columnNum > 0 && gameBoard.getBoardTile(rowNum - 1, columnNum - 1) == opponentPiece)
	{
		for (int i = rowNum - 2, j = columnNum - 2; i >= 0 && j >= 0; i--, j--)
		{
			if (gameBoard.getBoardTile(i, j) == ' ')
			{
				legalMoves.push_back(std::make_pair(i, j));
				break;
			}
			else if (gameBoard.getBoardTile(i, j) == currentPiece) break;
		}
	}
}
bool GameLogic::isGameOver() 
{
	if (pieceCounter == 64) return true;
	else return false;
}
void GameLogic::captureLeft(int rowNum, int columnNum, char currentPiece, char opponentPiece)
{
	for (int i = columnNum - 1; i >= 0; i--)
	{
		if (gameBoard.getBoardTile(rowNum, i) == currentPiece)
		{
			for (int j = columnNum - 1; j > i; j--) gameBoard.setBoardTile(currentPiece, rowNum, j);
			return;
		}
		else if (gameBoard.getBoardTile(rowNum, i) == ' ') return;
	}
}
void GameLogic::captureRight(int rowNum, int columnNum, char currentPiece, char opponentPiece)
{
	for (int i = columnNum + 1; i < 8; i++)
	{
		if (gameBoard.getBoardTile(rowNum, i) == currentPiece)
		{
			for (int j = columnNum + 1; j < i; j++) gameBoard.setBoardTile(currentPiece, rowNum, j);
			return;
		}
		else if (gameBoard.getBoardTile(rowNum, i) == ' ') return;
	}
}
void GameLogic::captureUp(int rowNum, int columnNum, char currentPiece, char opponentPiece)
{
	for (int i = rowNum - 1; i >= 0; i--)
	{
		if (gameBoard.getBoardTile(i, columnNum) == currentPiece)
		{
			for (int j = rowNum - 1; j > i; j--) gameBoard.setBoardTile(currentPiece, j, columnNum);
			return;
		}
		else if (gameBoard.getBoardTile(i, columnNum) == ' ') return;
	}
}
void GameLogic::captureDown(int rowNum, int columnNum, char currentPiece, char opponentPiece)
{
	for (int i = rowNum + 1; i < 8; i++)
	{
		if (gameBoard.getBoardTile(i, columnNum) == currentPiece)
		{
			for (int j = rowNum + 1; j < i; j++) gameBoard.setBoardTile(currentPiece, j, columnNum);
			return;
		}
		else if (gameBoard.getBoardTile(i, columnNum) == ' ') return;
	}
}
void GameLogic::captureUpLeft(int rowNum, int columnNum, char currentPiece, char opponentPiece)
{
	for (int i = rowNum - 1, j = columnNum - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (gameBoard.getBoardTile(i, j) == currentPiece)
		{
			for (int k = rowNum - 1, l = columnNum - 1; k > i && l > j; k--, l--) gameBoard.setBoardTile(currentPiece, k, l);
			return;
		}
		else if (gameBoard.getBoardTile(i, j) == ' ') return;
	}
}
void GameLogic::captureDownLeft(int rowNum, int columnNum, char currentPiece, char opponentPiece)
{
	for (int i = rowNum + 1, j = columnNum - 1; i < 8 && j >= 0; i++, j--)
	{
		if (gameBoard.getBoardTile(i, j) == currentPiece)
		{
			for (int k = rowNum + 1, l = columnNum - 1; k < i && l > j; k++, l--) gameBoard.setBoardTile(currentPiece, k, l);
			return;
		}
		else if (gameBoard.getBoardTile(i, j) == ' ') return;
	}
}
void GameLogic::captureUpRight(int rowNum, int columnNum, char currentPiece, char opponentPiece)
{
	for (int i = rowNum - 1, j = columnNum + 1; i >= 0 && j < 8; i--, j++)
	{
		if (gameBoard.getBoardTile(i, j) == currentPiece)
		{
			for (int k = rowNum - 1, l = columnNum + 1; k > i && l < j; k--, l++) gameBoard.setBoardTile(currentPiece, k, l);
			return;
		}
		else if (gameBoard.getBoardTile(i, j) == ' ') return;
	}
}
void GameLogic::captureDownRight(int rowNum, int columnNum, char currentPiece, char opponentPiece)
{
	for (int i = rowNum + 1, j = columnNum + 1; i < 8 && j < 8; i++, j++)
	{
		if (gameBoard.getBoardTile(i, j) == currentPiece)
		{
			for (int k = rowNum + 1, l = columnNum + 1; k < i && l < j; k++, l++) gameBoard.setBoardTile(currentPiece, k, l);
			return;
		}
		else if (gameBoard.getBoardTile(i, j) == ' ') return;
	}
}
void GameLogic::calculateScore(int& darkScore, int& lightScore)
{
	darkScore = 0;
	lightScore = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (gameBoard.getBoardTile(i, j) == 'L') lightScore++;
			else if (gameBoard.getBoardTile(i, j) == 'D') darkScore++;
		}
	}
}
void GameLogic::skipTurn() 
{ 
	moveCounter++;
	stalemateCounter++;
}
bool GameLogic::isStaleMate()
{
	if (stalemateCounter >= 2) return true;
	else return false;
}
void GameLogic::setCurrentAndOpponentPieces(char &currentPiece, char &opponentPiece)
{
	if (isLightPlayerTurn())
	{
		currentPiece = 'L';
		opponentPiece = 'D';
	}
	else
	{
		currentPiece = 'D';
		opponentPiece = 'L';
	}
}