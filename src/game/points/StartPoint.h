#pragma once
#include <random>
#include "../Pos.h"
#include "../../Util.h"
#include "../../Paintable.h"
class StartPoint : public Paintable {
public:
	const static int SIDE_LENGTH = 50;
	Pos pos;
	StartPoint();
	Gdiplus::Color getColor() const override;
};

