#pragma once
#include "../GameObject.h"
//this class draws the total score in the corner
class ScoreText : public GameObject{
public:
	ScoreText();

	void draw(Gdiplus::Graphics& g) const override;
};

