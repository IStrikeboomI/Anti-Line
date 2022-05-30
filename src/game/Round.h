#pragma once
#include "points/StartPoint.h"
#include "points/EndPoint.h"
//Each indiviual round will be stored using this class
class Round {
public:
	StartPoint startPoint;
	EndPoint endPoint;
	Round();
};

