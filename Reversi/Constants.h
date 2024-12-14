#pragma once
#include <map>
#include <string>
const char LIGHT_PIECE = 'L';
const char DARK_PIECE = 'D';
const char EMPTY_SPACE = ' ';

const std::string TIE_RETURN_STRING = "tie";

const int BOARD_HEIGHT = 8;
const int BOARD_WIDTH = 8;
const int PLAYER_STARTING_SCORE = 2;
const int PLAYER_COUNT = 2;
const int MOVE_COUNTER_INITIAL_VALUE = 1;
const int PIECE_COUNTER_INITIAL_VALUE = 4;

const std::map<std::string, std::pair<int, int>> MOVE_DIRECTIONS
{
	{"left", std::make_pair(0, -1)},
	{"right", std::make_pair(0, 1)},
	{"up", std::make_pair(-1, 0)},
	{"down", std::make_pair(1, 0)},
	{"upLeft", std::make_pair(-1, -1)},
	{"downLeft", std::make_pair(1, -1)},
	{"upRight", std::make_pair(-1, 1)},
	{"downRight", std::make_pair(1,1)}
};