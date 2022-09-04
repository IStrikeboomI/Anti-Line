#pragma once
#include <windows.h>
#include <gdiplus.h>

//an interface used for objects with color
class IPaintable {
public:
	virtual void draw(Gdiplus::Graphics& g) const = 0;
};