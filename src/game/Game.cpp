#include "Game.h"

Game::Game() {
	registerPaintables();
	registerTickables();
}
Game& Game::getInstance() {
	static Game g;
	return g;
}

void Game::registerPaintables() {
	paintableObjects.push_back(currentRound.startPoint);
	paintableObjects.push_back(currentRound.endPoint);
	paintableObjects.push_back(currentRound.player);
	paintableObjects.push_back(currentRound.stopwatch);
	paintableObjects.push_back(currentRound.scoreText);
	for (std::shared_ptr<Line>& l : currentRound.lines) {
		paintableObjects.push_back(*l);
	}
	paintableObjects.push_back(loseText);
	paintableObjects.push_back(winText);
}

void Game::registerTickables() {
	tickableObjects.push_back(currentRound);
	tickableObjects.push_back(currentRound.player);
	tickableObjects.push_back(currentRound.stopwatch);
	tickableObjects.push_back(loseText);
	tickableObjects.push_back(winText);
}

void Game::win() {
	newRound(RoundStatus::WON);
	//add 1 to the score
	score++;
}

void Game::lose() {
	newRound(RoundStatus::LOST);
	//reset score on loss;
	score = 0;
}

void Game::newRound(const RoundStatus& status) {
	inRound = false;
	this->status = status;
	currentRound = std::move(Round{});
	//because we have a vector of refernces, we can't copy them over or else they will be referring to the wrong objects
	//instead we clear both vectors, then re add them to the vectors
	paintableObjects.clear();
	tickableObjects.clear();
	registerTickables();
	registerPaintables();

}

void Game::update() {
	for (ITickable& t : tickableObjects) {
		t.update();
	}
}

void Game::displayRound() {
	inRound = true;
	status = RoundStatus::ONGOING;
}
