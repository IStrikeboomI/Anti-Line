#pragma once
#include "../Pos.h"
#include "../../Util.h"
#include "../../IPaintable.h"
class StartPoint : public IPaintable {
public:
	const static int SIDE_LENGTH = 50;
	Pos pos;
	StartPoint();
	Gdiplus::Color getColor() const override;
};

