#include "Game.h"

Game& Game::getInstance() {
	static Game g;
	return g;
}

void Game::win() {
	inRound = false;
	status = RoundStatus::WON;
	score++;
	currentRound = Round();
}

void Game::lose() {
	inRound = false;
	status = RoundStatus::LOST;
}

void Game::update() {
	currentRound.update();
}

void Game::newRound() {
	inRound = true;
}
