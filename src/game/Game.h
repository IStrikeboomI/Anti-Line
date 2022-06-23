#pragma once
#include "Round.h"
#include "../ITickable.h"
class Game : public ITickable{
public:
	Round currentRound;
	int score = 0;
	bool AIMode = false;
	bool inRound = true;

	static Game& getInstance();
	void win();
	void lose();
	void update() override;
};

