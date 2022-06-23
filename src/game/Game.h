#pragma once
#include "Round.h"
#include "../ITickable.h"
class Game : public ITickable {
public:
	Round currentRound;
	int score = 0;
	bool AIMode = false;
	bool inRound = true;

	void win();
	void lose();
	void update() override;
};

