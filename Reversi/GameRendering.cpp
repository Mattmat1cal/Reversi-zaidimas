#include <iostream>
#include <cstdio>
#include <regex>
#include "GameRendering.h"
#include "GameLogic.h"
void GameRendering::renderMenu() 
{
	bool invalidChoiceFlag = false;
	while (true)
	{
		system("cls");
		int option;
		std::cout << " _____                         _  \n";
		std::cout << "|  __ \\                       (_) \n";
		std::cout << "| |__) |_____   _____ _ __ ___ _  \n";
		std::cout << "|  _  // _ \\ \\ / / _ \\ '__/ __| | \n";
		std::cout << "| | \\ \\  __/\\ V /  __/ |  \\__ \\ | \n";
		std::cout << "|_|  \\_\\___| \\_/ \\___|_|  |___/_| \n";
		std::cout << "\n\n";
		std::cout << "________________________________________\n";
		std::cout << "Menu:\n";
		std::cout << "1 - Play\n";
		std::cout << "2 - Quit\n";
		if (invalidChoiceFlag) std::cout << "ERROR: Invalid choice\n";
		std::cout << "Enter number of choice you want: \n";
		std::cin >> option;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
		}
		switch (option)
		{
		case 1:
			invalidChoiceFlag = false;
			system("cls");
			renderPreGame();
			break;
		case 2:
			invalidChoiceFlag = false;
			exit(0);
		default:
			invalidChoiceFlag = true;
			break;
		}
	}
}
void GameRendering::renderGame() 
{
	bool invalidInputFlag = false;
	bool invalidMoveFlag = false;
	gameLogicHandler.resetGame();
	while (!gameLogicHandler.isBoardFull())
	{
		std::cin.ignore();
		system("cls");
		std::string currentPlayerName;
		std::string coordinates;
		renderBoard();
		if (gameLogicHandler.isLightPlayerTurn()) currentPlayerName = gameLogicHandler.getLightPlayer().getPlayerName();
		else currentPlayerName = gameLogicHandler.getDarkPlayer().getPlayerName();
		std::cout << "________________________________________\n";

		if (!gameLogicHandler.hasLegalMoves())
		{
			gameLogicHandler.skipTurn();
			std::cout << "Player " << currentPlayerName << " turn skipped, because there are no legal moves available\n";
			std::cout << "Press enter to continue\n";
			if (gameLogicHandler.isStaleMate())
			{
				renderGameEnd(true);
				return;
			}
		}
		else
		{
			if (invalidInputFlag) std::cout << "ERROR: Entered coordinates are invalid. Please use format (letternumber) (eg. a1, b3)\n";
			if (invalidMoveFlag) std::cout << "ERROR: Entered move is not allowed. Only moves that flip at least move piece can be played\n";
			std::cout << "Player " << currentPlayerName << " turn. Enter coordinates (or write \"quit\" to exit game): ";
			std::cin >> coordinates;
			if (coordinates == "quit")
			{
				std::cout << "Game was aborted. Press enter to go to menu";
				std::cin.ignore();
				std::cin.ignore();
				return;
			}
			else if (std::regex_match(coordinates, std::regex("^[a-h][1-8]$")))
			{
				if (!gameLogicHandler.processMove(coordinates)) invalidMoveFlag = true;
				else invalidMoveFlag = false;
				invalidInputFlag = false;
			}
			else invalidInputFlag = true;
		}
	}
	renderGameEnd(false);
}
void GameRendering::renderPreGame()
{
	std::string playerDark, playerLight;
	std::cout << "Enter dark piece player name: ";
	std::cin >> playerDark;
	gameLogicHandler.getDarkPlayer().setPlayerName(playerDark);
	std::cout << "Enter light piece player name: ";
	std::cin >> playerLight;
	gameLogicHandler.getLightPlayer().setPlayerName(playerLight);
	system("cls");
	renderGame();
}
void GameRendering::renderBoard() 
{
	std::cout << "   a  b  c  d  e  f  g  h\n";
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		std::cout << i + 1 << "  ";
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			std::cout << gameLogicHandler.getGameBoard().getBoardTile(i,j) << "  ";
		}
		std::cout << '\n';
	}
}
void GameRendering::renderGameEnd(bool isStalemate)
{
	std::cin.ignore();
	if(isStalemate) std::cout << "Game ended due to stalemate\n";
	std::cout << "Player " << gameLogicHandler.getDarkPlayer().getPlayerName() << " score: " << gameLogicHandler.getDarkPlayer().getPlayerScore() << '\n';
	std::cout << "Player " << gameLogicHandler.getLightPlayer().getPlayerName() << " score: " << gameLogicHandler.getLightPlayer().getPlayerScore() << '\n';
	if (gameLogicHandler.getWinningPlayerName() == TIE_RETURN_STRING) std::cout << "\nThe game ended in a tie!";
	else std::cout << "\nPlayer " << gameLogicHandler.getWinningPlayerName() << " wins!";
	std::cout << "\nPress enter to go back to the menu";
	std::cin.ignore();
}