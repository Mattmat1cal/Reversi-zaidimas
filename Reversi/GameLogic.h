#pragma once
#include "Constants.h"
#include "Board.h"
#include "Player.h"
#include <vector>
class GameLogic {
private:
	Board* gameBoard;
	Player playerLight, playerDark;
	int moveCounter, pieceCounter, stalemateCounter;
public:
	GameLogic();
	Board& getGameBoard();
	Player& getLightPlayer();
	Player& getDarkPlayer();
	bool hasLegalMoves();
	std::vector<std::pair<int,int>> calculateLegalMoves();
	bool isLightPlayerTurn();
	void resetGame();
	bool isBoardFull();
	bool processMove(std::string inputCoordinates);
	std::pair<int, int> parseCoordinates(std::string coordinates);
	void checkLegalMoves(std::vector<std::pair<int,int>>& legalMovesVector, int rowNum, int columnNum, char currentPiece, char opponentPiece);
	void capturePieces(std::pair<int, int> captureDirection, int rowNum, int columnNum, char currentPiece, char opponentPiece);
	std::string getWinningPlayerName();
	void skipTurn();
	bool isStaleMate();
	void setCurrentAndOpponentPieces(char& currentPiece, char& opponentPiece);
};