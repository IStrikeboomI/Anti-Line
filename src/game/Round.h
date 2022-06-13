#pragma once
#include "points/StartPoint.h"
#include "points/EndPoint.h"
#include "Player.h"
#include "../ITickable.h"
#include "Line.h"
#include <vector>
#include <functional>
//Each indiviual round will be stored using this class
class Round : public ITickable {
public:
	StartPoint startPoint;
	EndPoint endPoint;
	Player player;
	std::vector<std::shared_ptr<Line>> lines;
	Round();
	void update() override;
};

