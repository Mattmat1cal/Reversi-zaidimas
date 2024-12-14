#include "lib/catch_amalgamated.hpp"
#include "../GameLogic.h"

TEST_CASE("Testing correct move", "[GameLogic]")
{
	GameLogic gameLogicObj;
	SECTION("Resetting board, getting legal moves and making move")
	{
		gameLogicObj.resetGame();
		gameLogicObj.processMove("c4");
	}
	REQUIRE(gameLogicObj.getGameBoard().getBoardTile(3, 2) == DARK_PIECE);
	REQUIRE(gameLogicObj.getGameBoard().getBoardTile(3, 3) == DARK_PIECE);
	REQUIRE(gameLogicObj.getGameBoard().getBoardTile(3, 4) == DARK_PIECE);
	REQUIRE(gameLogicObj.getGameBoard().getBoardTile(4, 3) == DARK_PIECE);
	REQUIRE(gameLogicObj.getGameBoard().getBoardTile(4, 4) == LIGHT_PIECE);
}