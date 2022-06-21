#pragma once
#include "Pos.h"
#include "Line.h"
#include "../Util.h"
#include <vector>
#include <cmath>
//In order to make every round at least winnable we make a pre determined path that no lines can generate near
//this path can be a simple line or something complex but just needs to be from point A (starting point) to point B (ending point)
class PredeterminedPath {
private:
	//this can also serve as the hyponetuese of the triangle created by the line
	static const int LINE_LENGTH = 25;
public:
	std::vector<std::shared_ptr<Line>> lines;

	PredeterminedPath(const Pos& start, const Pos& end);
	//this checks for if the line passed is within the distnace passed of the path
	bool isLineNear(const Line& line, int distance) const;
};

