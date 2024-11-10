#pragma once
#include <string>
class Player 
{
private:
	std::string playerName;
public:
	void setPlayerName(std::string name);
	std::string getPlayerName();
};
