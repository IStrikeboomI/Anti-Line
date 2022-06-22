#pragma once

#include "Point.h"
#include "../../Util.h"
class StartPoint : public Point {
public:
	StartPoint();

	Gdiplus::Color getColor() const override;
};

