#pragma once
#include "../Util.h"
#include "Pos.h"
#include "../Paintable.h"
#include "../Util.h"
#include "../Direction.h"
class Player : public Paintable{
private:
	//holds the alpha and rgb for the player color
	//the way it works is by generating a random RGB value which is between 0 and 16777216 (FFFFFF in hex)
	//then it uses "| 0xFF000000" to set the alpha of it to max because argb holds alpha first
	int argb = Util::random(0, 0xFFFFFF) | 0xFF000000;
	float xAxisAcceleration = 0, xAxisvelocity = 0, yAxisAcceleration = 0, yAxisVelocity = 0;
	const float MAX_ACCELERATION = 2, MAX_VELOCITY = 5;
	Direction direction = Direction::UP;
public:
	const static int SIDE_LENGTH = 30;
	Pos pos;

	Player();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void move();
	void idle();
	Gdiplus::Color getColor() const override;
};

