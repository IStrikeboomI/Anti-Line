#pragma once
#include "Pos.h"
//In order to make every round at least winnable we make a pre determined path that no lines can generate near
//this path can be a simple line or something complex but just needs to be from point A (starting point) to point B (ending point)
class PredeterminedPath {
private:
	Pos start, end;
public:
	PredeterminedPath(Pos start, Pos end);
};

