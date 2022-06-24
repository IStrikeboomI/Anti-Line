#include "Game.h"

Game& Game::getInstance() {
	static Game g;
	return g;
}

void Game::win() {
	inRound = false;
	score++;
}

void Game::lose() {
	inRound = false;
}

void Game::update() {
	currentRound.update();
}

void Game::newRound() {
	currentRound = Round();
}
