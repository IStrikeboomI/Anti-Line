#pragma once
#include "../Util.h"
#include "Pos.h"
#include "../Paintable.h"
#include "../ITickable.h"
#include "../Util.h"
class Player : public Paintable, public ITickable {
private:
	//holds the alpha and rgb for the player color
	//the way it works is by generating a random RGB value which is between 0 and 16777216 (FFFFFF in hex)
	//then it uses the bit mask "| 0xFF000000" to set the alpha of it to max because argb holds alpha first
	int argb = Util::random(0, 0xFFFFFF) | 0xFF000000;
	//used for movement in both axes respectively
	double xAxisAcceleration = 0, xAxisVelocity = 0, yAxisAcceleration = 0, yAxisVelocity = 0;
	//used for capping out acceleration and velocity so we don't go too fast
	constexpr static double MAX_ACCELERATION = 5, MAX_VELOCITY = 10, ACCELERATION_INCREASE_AMOUNT = 1;
public:

	const static int SIDE_LENGTH = 30;
	Pos pos;

	Player();
	//these 4 are used for moving the character in the desired direction
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();	

	//the player doesn't just move staticly, it insteads slips around like ice
	//the 4 functions above add velocity and acceleration but this method handles them to move the character
	void update() override;
	void draw(Gdiplus::Graphics& g) const override;
};

