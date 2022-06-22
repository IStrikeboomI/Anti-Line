#pragma once
#include "Round.h"
class Game {
public:
	Round currentRound;
	int score = 0;
	bool AIMode = false;
	bool inRound = true;
};

