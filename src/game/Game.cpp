#include "Game.h"

Game& Game::getInstance() {
	static Game g;
	return g;
}

void Game::win() {
}

void Game::lose() {
}

void Game::update() {
	currentRound.update();
}
