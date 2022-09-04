#pragma once
#include "points/StartPoint.h"
#include "points/EndPoint.h"
#include "Player.h"
#include "../ITickable.h"
#include "Line.h"
#include "PredeterminedPath.h"
#include <vector>
//Each indiviual round will be stored using this class
class Round : public ITickable {
public:
	std::vector<std::reference_wrapper<IPaintable>> paintableObjects;
	std::vector<std::reference_wrapper<ITickable>> tickableObjects;

	StartPoint startPoint;
	EndPoint endPoint;
	Player player;
	PredeterminedPath path;
	std::vector<std::shared_ptr<Line>> lines;

	Round();
	void update() override;
	//registry methods for the two vectors above
	void registerPaintables();
	void registerTickables();
	//we need to overload the assignment operator
	//used when a new round starts
	Round& operator=(const Round&);
	//rule of three because of the above line
	Round(const Round&) = default;
	~Round() = default;
};

