#pragma once
#include <array>
class Board
{
private:
	char boardTiles[8][8];
public:
	char getBoardTile(int x, int y);
	void setBoardTile(char tileValue, int tileX, int tileY);
	void resetBoard();
};