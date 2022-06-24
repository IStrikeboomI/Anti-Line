#include "Game.h"

Game& Game::getInstance() {
	static Game g;
	return g;
}

void Game::win() {
	//inRound = false;
	score++;
	currentRound = Round();
}

void Game::lose() {
	inRound = false;
}

void Game::update() {
	currentRound.update();
}
