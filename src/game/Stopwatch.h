#pragma once
#include "GameObject.h"
#include <string>
#include <sstream>
#include <format>
//this show the total time elapsed in the format of M:SS.mm (m is milisecond)
class Stopwatch : public GameObject{
private:
	unsigned int elapsedTicks = 0;
public:
	Stopwatch();

	void draw(Gdiplus::Graphics& g) const override;
	void update() override;
};

