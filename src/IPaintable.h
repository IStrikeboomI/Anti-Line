#pragma once
#include <windows.h>
#include <gdiplus.h>

//an interface used for objects with color
class IPaintable {
	virtual Gdiplus::Color getColor() const = 0;
};