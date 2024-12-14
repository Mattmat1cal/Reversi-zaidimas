#include "lib/catch_amalgamated.hpp"
#include "../Board.h"
#include "../Constants.h"

Board* board = &Board::getInstance();

TEST_CASE("Game board is initialized correctly" "[Board]")
{
	SECTION("Calling board reset") 
	{
		board->resetBoard();
	}
	REQUIRE(board->getBoardTile(3, 3) == LIGHT_PIECE);
	REQUIRE(board->getBoardTile(3, 4) == DARK_PIECE);
	REQUIRE(board->getBoardTile(4, 3) == DARK_PIECE);
	REQUIRE(board->getBoardTile(4, 4) == LIGHT_PIECE);
}