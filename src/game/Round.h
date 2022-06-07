#pragma once
#include "points/StartPoint.h"
#include "points/EndPoint.h"
#include "Player.h"
#include "../ITickable.h"
//Each indiviual round will be stored using this class
class Round : public ITickable {
public:
	StartPoint startPoint;
	EndPoint endPoint;
	Round();
	Player player;
	void update() override;
};

