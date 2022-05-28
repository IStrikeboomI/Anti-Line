#pragma once
#include "points/StartPoint.h"
//Each indiviual round will be stored using this class
class Round {
private:
	int score = 0;
public:
	StartPoint startPoint;
	Round();
	int getScore();
};

