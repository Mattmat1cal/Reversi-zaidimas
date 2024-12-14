#pragma once
#include "GameLogic.h"
class GameRendering 
{
private:
	GameLogic gameLogicHandler;
public:
	void renderMenu();
	void renderBoard();
	void renderGame();
	void renderPreGame();
	void renderGameEnd(bool isStalemate);
};