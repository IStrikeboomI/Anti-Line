#pragma once
#include "EndText.h"
class WinText : public EndText {
public:
	WinText();

	void draw(Gdiplus::Graphics& g) const override;
};

