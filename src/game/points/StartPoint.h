#pragma once

#include "Point.h"
#include "../../Util.h"
//this class is the green square at the start of the map to start the round
class StartPoint : public Point {
public:
	StartPoint();

	void draw(Gdiplus::Graphics& g) const override;
};

