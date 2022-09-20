#pragma once
#include "../Paintable.h"
//this class draws the total score in the corner
class ScoreText : public Paintable{
public:
	ScoreText();

	void draw(Gdiplus::Graphics& g) const override;
};

