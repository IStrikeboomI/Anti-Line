#pragma once
#include "Pos.h"
#include "../Paintable.h"
#include "../Util.h"
class Player : public Paintable{
private:
	//holds the alpha and rgb for the player color
	//the way it works is by generating a random RGB value which is between 0 and 16777216 (FFFFFF in hex)
	//then it uses "| 0xFF000000" to set the alpha of it to max because argb holds alpha first
	int argb = Util::random(0, 0xFFFFFF) | 0xFF000000;
public:
	const static int SIDE_LENGTH = 30;
	Pos pos;

	Player();
	void moveUp(int distance = 1);
	void moveDown(int distance = 1);
	void moveLeft(int distance = 1);
	void moveRight(int distance = 1);
	Gdiplus::Color getColor() const override;
};

