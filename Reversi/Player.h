#pragma once
#include <string>
class Player 
{
private:
	std::string playerName;
	char playerPiece;
	int playerScore;
public:
	void setPlayerName(std::string name);
	std::string getPlayerName();
	void setPlayerPiece(char piece);
	char getPlayerPiece();
	void resetPlayerScore();
	void increasePlayerScore();
	void decreasePlayerScore();
	int getPlayerScore();
};
