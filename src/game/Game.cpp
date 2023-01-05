#include "Game.h"

Game::Game() {
	registerObjects();
}
Game& Game::getInstance() {
	static Game g;
	return g;
}


void Game::registerObjects() {
	gameObjects.push_back(currentRound.startPoint);
	gameObjects.push_back(currentRound.endPoint);
	gameObjects.push_back(currentRound.player);
	gameObjects.push_back(currentRound.stopwatch);
	gameObjects.push_back(currentRound.scoreText);
	for (std::shared_ptr<Line>& l : currentRound.lines) {
		gameObjects.push_back(*l);
	}
	gameObjects.push_back(loseText);
	gameObjects.push_back(winText);
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
	//because we have a vector of references, we can't copy them over or else they will be referring to the wrong objects
	//instead the vector, then re add them to the vector
	gameObjects.clear();
	registerObjects();
}

void Game::update() {
	for (GameObject& g : gameObjects) {
		g.update();
	}
}

void Game::displayRound() {
	inRound = true;
	status = RoundStatus::ONGOING;
}
