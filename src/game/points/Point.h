#pragma once
#include "../Pos.h"
#include "../Player.h"
#include "../../Paintable.h"

class Point : public Paintable {
public:
	const static int SIDE_LENGTH = 50;
	Pos pos;

	Point(int x, int y) : pos(x, y, SIDE_LENGTH, SIDE_LENGTH) {};

	virtual void onPlayerCollide(Player& p) {};
	virtual void draw(Gdiplus::Graphics& g) const override = 0;
};