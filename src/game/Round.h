#pragma once
#include "points/StartPoint.h"
#include "points/EndPoint.h"
#include "Player.h"
#include "Line.h"
#include "PredeterminedPath.h"
#include "Stopwatch.h"
#include "text/ScoreText.h"
#include <vector>
//Each indiviual round will be stored using this class
class Round {
public:
	StartPoint startPoint;
	EndPoint endPoint;
	Player player;
	PredeterminedPath path;
	Stopwatch stopwatch;
	ScoreText scoreText;
	std::vector<std::shared_ptr<Line>> lines;

	Round();
	void update();
	//we need to overload the assignment operator
	//used when a new round starts
	Round& operator=(const Round&) = default;
	//rule of three because of the above line
	Round(const Round&) = default;
	~Round() = default;
};

