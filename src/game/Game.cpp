#include "Game.h"
void Game::win() {
}

Game& Game::getInstance() {
	static Game g;
	return g;
}

void Game::lose() {
}

void Game::update() {
	currentRound.update();
}
