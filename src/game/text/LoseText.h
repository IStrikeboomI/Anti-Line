#pragma once
#include "EndText.h"
class LoseText : public EndText {
public:
	LoseText();
	void draw(Gdiplus::Graphics& g) const override;
};

