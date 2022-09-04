#include "Game.h"

Game& Game::getInstance() {
	static Game g;
	return g;
}

void Game::win() {
	inRound = false;
	status = RoundStatus::WON;
	score++;
	currentRound = std::move(Round{});
}

void Game::lose() {
	inRound = false;
	status = RoundStatus::LOST;
	score = 0;
	currentRound = std::move(Round{});
}

void Game::update() {
	currentRound.update();
}

void Game::displayRound() {
	inRound = true;
	status = RoundStatus::ONGOING;
}
