#include "lib/catch_amalgamated.hpp"
#include "../GameLogic.h"

TEST_CASE("Testing stalemate state", "[GameLogic]")
{
	GameLogic gameLogicObj;
	SECTION("Resetting game and making moves for shortest stalemate")
	{
		gameLogicObj.resetGame();
		gameLogicObj.processMove("d3");
		gameLogicObj.processMove("c3");
		gameLogicObj.processMove("b3");
		gameLogicObj.processMove("d2");
		gameLogicObj.processMove("e1");
		gameLogicObj.processMove("d6");
		gameLogicObj.processMove("d7");
		gameLogicObj.processMove("e3");
		gameLogicObj.processMove("f4");
	}
	REQUIRE(gameLogicObj.hasLegalMoves() == false);
	gameLogicObj.skipTurn();
	REQUIRE(gameLogicObj.hasLegalMoves() == false);
	gameLogicObj.skipTurn();
	REQUIRE(gameLogicObj.isStaleMate() == true);
}