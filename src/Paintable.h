#pragma once
#include <windows.h>
#include <gdiplus.h>
//a class used for objects that are drawn to the applciation
//needs to be registered in the Game class
class Paintable {
public:
	//this method should be used only for drawing and needs to be overriden
	virtual void draw(Gdiplus::Graphics& g) const = 0;

	//some objects need to be drawn at certain times (eg. win/loss text)
	//override this if you need to draw at a time that is not during the round
	virtual bool canDraw();
};
