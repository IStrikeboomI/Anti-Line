#pragma once

#include "../../Util.h"
#include "Point.h"
class EndPoint : public Point{
public:
	EndPoint();

	void onPlayerCollide(Player& p) override;
	void draw(Gdiplus::Graphics& g) const override;
};

