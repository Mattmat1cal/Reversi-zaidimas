#include "GameLogic.h"
#include <iostream>
#include <vector>

GameLogic::GameLogic()
{
	gameBoard = &Board::getInstance();
}

Board& GameLogic::getGameBoard() { return *gameBoard; }

Player& GameLogic::getLightPlayer() { return this->playerLight; }

Player& GameLogic::getDarkPlayer() { return this->playerDark; }

bool GameLogic::isLightPlayerTurn() { return (moveCounter % PLAYER_COUNT == 0); }

void GameLogic::resetGame()
{
	moveCounter = MOVE_COUNTER_INITIAL_VALUE;
	pieceCounter = PIECE_COUNTER_INITIAL_VALUE;
	stalemateCounter = 0;
	gameBoard->resetBoard();
	playerLight.setPlayerPiece(LIGHT_PIECE);
	playerLight.resetPlayerScore();
	playerDark.setPlayerPiece(DARK_PIECE);
	playerDark.resetPlayerScore();
}
bool GameLogic::processMove(std::string inputCoordinates)
{
	std::pair<int, int> coordinates = parseCoordinates(inputCoordinates);
	char currentPiece, opponentPiece;
	setCurrentAndOpponentPieces(currentPiece, opponentPiece);
	std::vector<std::pair<int, int>> legalMovesVector = calculateLegalMoves();
	if (std::find(legalMovesVector.begin(), legalMovesVector.end(), coordinates) != legalMovesVector.end())
	{
		gameBoard->setBoardTile(currentPiece, coordinates.first, coordinates.second);
		if (currentPiece == LIGHT_PIECE) playerLight.increasePlayerScore();
		else playerDark.increasePlayerScore();

		for (auto direction : MOVE_DIRECTIONS)
		{
			if (gameBoard->getBoardTile(coordinates.first + direction.second.first, coordinates.second + direction.second.second) == opponentPiece)
			{
				capturePieces(direction.second, coordinates.first, coordinates.second, currentPiece, opponentPiece);
			}
		}

		moveCounter++;
		pieceCounter++;
		stalemateCounter = 0;
		return true;
	}
	else return false;
}
std::pair<int, int> GameLogic::parseCoordinates(std::string coordinates)
{
	return std::make_pair(coordinates.at(1) - '1', coordinates.at(0) - 'a');
}
bool GameLogic::hasLegalMoves()
{
	if (calculateLegalMoves().empty()) return false;
	else return true;
}
std::vector<std::pair<int,int>> GameLogic::calculateLegalMoves()
{
	std::vector<std::pair<int, int>> legalMovesVector;
	char currentPiece, opponentPiece;
	setCurrentAndOpponentPieces(currentPiece, opponentPiece);
	for (int i = 0; i < BOARD_HEIGHT; i++) 
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (gameBoard->getBoardTile(i, j) == currentPiece) checkLegalMoves(legalMovesVector, i, j, currentPiece, opponentPiece);
		}
	}
	return legalMovesVector;
}
void GameLogic::checkLegalMoves(std::vector<std::pair<int, int>>& legalMovesVector, int rowNum, int columnNum, char currentPiece, char opponentPiece)
{
	for (auto moveDirection : MOVE_DIRECTIONS)
	{
		if (columnNum + moveDirection.second.second > 0 && columnNum + moveDirection.second.second < BOARD_WIDTH &&
			rowNum + moveDirection.second.first > 0 && rowNum + moveDirection.second.first < BOARD_HEIGHT &&
			gameBoard->getBoardTile(rowNum + moveDirection.second.first, columnNum + moveDirection.second.second) == opponentPiece)
		{
			for (int i = rowNum + moveDirection.second.first * 2, j = columnNum + moveDirection.second.second * 2;
				i < BOARD_HEIGHT && i >= 0 && j < BOARD_WIDTH && j >= 0;
				i += moveDirection.second.first, j += moveDirection.second.second)
			{
				if (gameBoard->getBoardTile(i, j) == EMPTY_SPACE)
				{
					legalMovesVector.push_back(std::make_pair(i, j));
					break;
				}
				else if (gameBoard->getBoardTile(i, j) == currentPiece) break;
			}
		}
	}
}
bool GameLogic::isBoardFull() 
{
	if (pieceCounter == 64) return true;
	else return false;
}
void GameLogic::capturePieces(std::pair<int, int> captureDirection, int rowNum, int columnNum, char currentPiece, char opponentPiece)
{
	for (int i = rowNum + captureDirection.first, j = columnNum + captureDirection.second;
		i >= 0 && i < BOARD_HEIGHT && j >= 0 && j < BOARD_WIDTH;
		i += captureDirection.first, j += captureDirection.second)
	{
		if (gameBoard->getBoardTile(i, j) == currentPiece)
		{
			for (int k = rowNum + captureDirection.first, l = columnNum + captureDirection.second;
				k != i || l != j;
				k += captureDirection.first, l += captureDirection.second)
			{
				gameBoard->setBoardTile(currentPiece, k, l);
				if (currentPiece == LIGHT_PIECE)
				{
					playerLight.increasePlayerScore();
					playerDark.decreasePlayerScore();
				}
				else
				{
					playerLight.decreasePlayerScore();
					playerDark.increasePlayerScore();
				}
			}
			return;
		}
		else if (gameBoard->getBoardTile(i, j) == EMPTY_SPACE) return;
	}
}
std::string GameLogic::getWinningPlayerName()
{
	if (playerLight.getPlayerScore() > playerDark.getPlayerScore()) return playerLight.getPlayerName();
	else if (playerDark.getPlayerScore() > playerLight.getPlayerScore()) return playerDark.getPlayerName();
	else return TIE_RETURN_STRING;
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
		currentPiece = getLightPlayer().getPlayerPiece();
		opponentPiece = getDarkPlayer().getPlayerPiece();
	}
	else
	{
		currentPiece = getDarkPlayer().getPlayerPiece();
		opponentPiece = getLightPlayer().getPlayerPiece();
	}
}