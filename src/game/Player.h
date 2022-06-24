#pragma once
#include "../Util.h"
#include "Pos.h"
#include "../IPaintable.h"
#include "../ITickable.h"
#include "../Util.h"
class Player : public IPaintable, public ITickable {
private:
	//holds the alpha and rgb for the player color
	//the way it works is by generating a random RGB value which is between 0 and 16777216 (FFFFFF in hex)
	//then it uses "| 0xFF000000" to set the alpha of it to max because argb holds alpha first
	int argb = Util::random(0, 0xFFFFFF) | 0xFF000000;
	//used for movement in both axes respectively
	float xAxisAcceleration = 0, xAxisVelocity = 0, yAxisAcceleration = 0, yAxisVelocity = 0;
	//used for capping out acceleration and velocity so we don't go too fast
	constexpr static float MAX_ACCELERATION = 5, MAX_VELOCITY = 10, ACCELERATION_INCREASE_AMOUNT = 1;
public:

	const static int SIDE_LENGTH = 30;
	Pos pos;

	Player();
	//these 4 are used for moving the character in the desired direction
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	//overriden from ITickable.h
	void update() override;
	//overriden from Paintable.h
	Gdiplus::Color getColor() const override;
};

