#pragma once
#include "Pos.h"
#include "../IPaintable.h"
class Line : public IPaintable {
public:
	Pos startPos;
	Pos endPos;

	Line(int x1,int y1,int x2,int y2);
	Gdiplus::Color getColor() const override;
};

