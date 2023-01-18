#pragma once
#include "../Pos.h"
#include "../Player.h"
#include "../GameObject.h"

class Point : public GameObject {
public:
	constexpr static int SIDE_LENGTH = 50;
	Pos pos;

	Point(int x, int y) : pos(x, y, SIDE_LENGTH, SIDE_LENGTH) {};

	virtual void onPlayerCollision(Player& p) override {};
	virtual bool isPlayerCollided(Player& p) override { return pos.isCollided(p.pos); };
	virtual void draw(Gdiplus::Graphics& g) const override = 0;
};