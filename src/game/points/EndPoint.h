#pragma once
#include "../Pos.h"
#include "../../Util.h"
#include "../../IPaintable.h"
class EndPoint : public IPaintable{
public:
	const static int SIDE_LENGTH = 50;
	Pos pos;
	EndPoint();
	Gdiplus::Color getColor() const override;
};

