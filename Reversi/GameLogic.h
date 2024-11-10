#pragma once
#include "Board.h"
#include "Player.h"
#include <vector>
class GameLogic {
private:
	Board gameBoard;
	Player playerLight, playerDark;
	int moveCounter, pieceCounter, stalemateCounter;
public:
	Board& getGameBoard();
	Player& getLightPlayer();
	Player& getDarkPlayer();
	bool isLightPlayerTurn();
	void resetGame();
	bool isGameOver();
	bool processMove(std::string inputCoordinates, std::vector<std::pair<int,int>> legalMoves);
	void parseCoordinates(std::string coordinates, std::pair<int, int>& parsedCoordinates);
	std::vector<std::pair<int, int>> getLegalMoves();
	void checkColumn(std::vector<std::pair<int, int>> &legalMoves, int rowNum, int columnNum, char currentPiece, char opponentPiece);
	void checkRow(std::vector<std::pair<int, int>>& legalMoves, int rowNum, int columnNum, char currentPiece, char opponentPiece);
	void checkDiagonals(std::vector<std::pair<int, int>>& legalMoves, int rowNum, int columnNum, char currentPiece, char opponentPiece);
	void captureLeft(int rowNum, int columnNum, char currentPiece, char opponentPiece);
	void captureRight(int rowNum, int columnNum, char currentPiece, char opponentPiece);
	void captureUp(int rowNum, int columnNum, char currentPiece, char opponentPiece);
	void captureDown(int rowNum, int columnNum, char currentPiece, char opponentPiece);
	void captureUpLeft(int rowNum, int columnNum, char currentPiece, char opponentPiece);
	void captureUpRight(int rowNum, int columnNum, char currentPiece, char opponentPiece);
	void captureDownLeft(int rowNum, int columnNum, char currentPiece, char opponentPiece);
	void captureDownRight(int rowNum, int columnNum, char currentPiece, char opponentPiece);
	void calculateScore(int &darkScore, int &lightScore);
	void skipTurn();
	bool isStaleMate();
	void setCurrentAndOpponentPieces(char& currentPiece, char& opponentPiece);
};