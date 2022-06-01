#pragma once
#include "points/StartPoint.h"
#include "points/EndPoint.h"
#include "Player.h"
//Each indiviual round will be stored using this class
class Round {
public:
	StartPoint startPoint;
	EndPoint endPoint;
	Round();
	Player player;
};

