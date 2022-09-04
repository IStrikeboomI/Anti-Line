#pragma once

#include "Point.h"
#include "../../Util.h"
class StartPoint : public Point {
public:
	StartPoint();

	void draw(Gdiplus::Graphics& g) const override;
};

