#pragma once
#include "../Paintable.h"
#include "../ITickable.h"
#include <string>
#include <sstream>
#include <format>
//this show the total time elapsed in the format of M:SS.mm (m is milisecond)
class Stopwatch : public Paintable, public ITickable{
private:
	unsigned int elapsedTicks = 0;
public:
	Stopwatch();

	void draw(Gdiplus::Graphics& g) const override;
	void update() override;
};

