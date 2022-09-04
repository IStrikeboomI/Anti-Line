#include "Game.h"

Game& Game::getInstance() {
	static Game g;
	return g;
}

void Game::win() {
	inRound = false;
	status = RoundStatus::WON;
	//add 1 to the score
	score++;
	//we don't need to handle the pos from other rounds
	Pos::clearInstances();
	currentRound = std::move(Round{});
}

void Game::lose() {
	inRound = false;
	status = RoundStatus::LOST;
	//reset score on loss;
	score = 0;
	//we don't need to handle the pos from other rounds
	Pos::clearInstances();
	currentRound = std::move(Round{});
}

void Game::update() {
	currentRound.update();
}

void Game::displayRound() {
	inRound = true;
	status = RoundStatus::ONGOING;
}
