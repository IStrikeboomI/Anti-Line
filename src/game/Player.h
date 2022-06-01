#pragma once
#include "Pos.h"
class Player {
private:
	void moveUp(int distance = 1);
	void moveDown(int distance = 1);
	void moveLeft(int distance = 1);
	void moveRight(int distance = 1);
public:
	const static int SIDE_LENGTH = 30;
	Pos pos;

	Player();
	void handleKeyboardInput(int keycode);
};

