#pragma once
#include "Round.h"
#include "../ITickable.h"
#include "../IPaintable.h"
#include "RoundStatus.h"
//Used for storing the game instance
//Also a bridge class between the game internals and the UI
class Game : public ITickable{
private:
	//we don't need a public constructor because this is a SINGLETON
	Game() {};
public:
	//default FPS for game
	constexpr static int FPS = 60;

	Round currentRound;
	unsigned int score = 0;
	bool AIMode = false;
	bool inRound = true;
	RoundStatus status = RoundStatus::ONGOING;

	//this class is a singleton
	static Game& getInstance();
	//these 2 methods create a new round
	void win();
	void lose();
	//dispatches update to the round
	void update() override;
	void displayRound();
	//don't implement these two or else we might get multiple copies
	Game(const Game&) = delete;
	void operator=(const Game&) = delete;
};

