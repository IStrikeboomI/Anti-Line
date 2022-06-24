#pragma once
#include "Round.h"
#include "../ITickable.h"
class Game : public ITickable{
private:
	//we don't need to initalize anything
	Game() {};
public:
	Round currentRound;
	int score = 0;
	bool AIMode = false;
	bool inRound = true;

	//this class is a singleton
	static Game& getInstance();
	void win();
	void lose();
	void update() override;
	//don't implement these two or else we might get multiple copies
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;
};

