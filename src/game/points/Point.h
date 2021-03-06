#pragma once
#include "../Pos.h"
#include "../Player.h"
#include "../../IPaintable.h"

class Point : public IPaintable {
public:
	const static int SIDE_LENGTH = 50;
	Pos pos;

	Point(int x,int y) : pos(x,y,SIDE_LENGTH,SIDE_LENGTH) {};

	virtual void onPlayerCollide(Player p) {};
	virtual Gdiplus::Color getColor() const override = 0;
};