#include "Board.h"
char Board::getBoardTile(int x, int y) { return boardTiles[x][y]; }
void Board::setBoardTile(char tileValue, int tileX, int tileY) { boardTiles[tileX][tileY] = tileValue; }
void Board::resetBoard()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			boardTiles[i][j] = ' ';
		}
	}
	boardTiles[3][3] = 'L';
	boardTiles[3][4] = 'D';
	boardTiles[4][3] = 'D';
	boardTiles[4][4] = 'L';
}