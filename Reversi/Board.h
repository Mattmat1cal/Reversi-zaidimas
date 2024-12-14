#pragma once
#include "Constants.h"
#include <array>
class Board
{
private:
	char boardTiles[BOARD_HEIGHT][BOARD_WIDTH];
	Board() {};
public:
	void operator=(const Board& obj) = delete;
	Board(const Board& obj) = delete;
	static Board& getInstance();
	char getBoardTile(int x, int y);
	void setBoardTile(char tileValue, int tileX, int tileY);
	void resetBoard();
};