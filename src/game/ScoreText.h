#pragma once
#include "../IPaintable.h"
class ScoreText : public IPaintable{
public:
	ScoreText();

	void draw(Gdiplus::Graphics& g) const override;
};

