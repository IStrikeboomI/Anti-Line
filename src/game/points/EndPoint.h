#pragma once

#include "../../Util.h"
#include "Point.h"
class EndPoint : public Point{
public:
	EndPoint();

	void onPlayerCollide(Player p) override;
	Gdiplus::Color getColor() const override;
};

