#pragma once
#include "Round.h"
#include "../ITickable.h"
#include "../IPaintable.h"
#include "RoundStatus.h"
//Used for storing the game instance
//Also a bridge class between the game internals and the UI
class Game{
private:
	//we don't need a public constructor because this is a SINGLETON
	Game() {};
public:
	Round currentRound;
	int score = 0;
	bool AIMode = false;
	bool inRound = true;
	RoundStatus status = RoundStatus::ONGOING;

	//this class is a singleton
	static Game& getInstance();
	//these 2 methods create a new round
	void win();
	void lose();
	//dispatches update to the round
	void update();
	void displayRound();
	//don't implement these two or else we might get multiple copies
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;
};

