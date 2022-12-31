#pragma once
#include "../Pos.h"
#include "../Player.h"
#include "../../Paintable.h"
#include "../../IPlayerCollidable.h"

class Point : public Paintable, public IPlayerCollidable {
public:
	constexpr static int SIDE_LENGTH = 50;
	Pos pos;

	Point(int x, int y) : pos(x, y, SIDE_LENGTH, SIDE_LENGTH) {};

	virtual void onPlayerCollision(Player& p) {};
	virtual void draw(Gdiplus::Graphics& g) const override = 0;
};