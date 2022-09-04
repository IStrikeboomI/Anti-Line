#pragma once
#include "Pos.h"
#include "../IPaintable.h"
class Line : public IPaintable {
public:
	Pos startPos;
	Pos endPos;

	Line(int x1,int y1,int x2,int y2);
	void draw(Gdiplus::Graphics& g) const override;
	//used for chekcing if two lines intersect
	bool doLinesIntersect(const Line& l) const;
};

