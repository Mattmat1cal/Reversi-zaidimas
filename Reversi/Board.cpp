#include "Board.h"

Board& Board::getInstance()
{
	static Board boardInstance;
	return boardInstance;
}

char Board::getBoardTile(int x, int y) 
{ 
	return boardTiles[x][y]; 
}

void Board::setBoardTile(char tileValue, int tileX, int tileY)
{ 
	boardTiles[tileX][tileY] = tileValue; 
}

void Board::resetBoard()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			boardTiles[i][j] = EMPTY_SPACE;
		}
	}
	boardTiles[3][3] = LIGHT_PIECE;
	boardTiles[3][4] = DARK_PIECE;
	boardTiles[4][3] = DARK_PIECE;
	boardTiles[4][4] = LIGHT_PIECE;
}