#pragma once
#include "Pos.h"
#include "../Paintable.h"
//this class represents all the lines the player can't touch or else they lose
class Line : public Paintable {
public:
	Pos startPos;
	Pos endPos;

	Line(int x1,int y1,int x2,int y2);
	void draw(Gdiplus::Graphics& g) const override;
	//used for chekcing if two lines intersect
	bool doLinesIntersect(const Line& l) const;
};

