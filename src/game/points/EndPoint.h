#pragma once
#include <random>
#include "../Pos.h"
#include "../../Util.h"
#include "../../Paintable.h"
class EndPoint : public Paintable{
public:
	const static int SIDE_LENGTH = 50;
	Pos pos;
	EndPoint();
	Gdiplus::Color getColor() const override;
};

