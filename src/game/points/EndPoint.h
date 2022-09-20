#pragma once

#include "../../Util.h"
#include "Point.h"
//this class is the red square at the end of the map to win the round
class EndPoint : public Point{
public:
	EndPoint();

	void onPlayerCollide(Player& p) override;
	void draw(Gdiplus::Graphics& g) const override;
};

