#pragma once
#include "../Paintable.h"
class ScoreText : public Paintable{
public:
	ScoreText();

	void draw(Gdiplus::Graphics& g) const override;
};

