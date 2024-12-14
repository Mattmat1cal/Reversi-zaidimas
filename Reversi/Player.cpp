#include "Player.h"
#include "Constants.h"
void Player::setPlayerName(std::string name) { this->playerName = name; }

std::string Player::getPlayerName() { return this->playerName; }

void Player::setPlayerPiece(char playerPiece) { this->playerPiece = playerPiece; }

char Player::getPlayerPiece() { return this->playerPiece; }

void Player::resetPlayerScore() { this->playerScore = PLAYER_STARTING_SCORE; }

void Player::increasePlayerScore() { this->playerScore++; }

void Player::decreasePlayerScore() { this->playerScore--; }

int Player::getPlayerScore() { return this->playerScore; }