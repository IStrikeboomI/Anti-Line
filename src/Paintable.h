#pragma once
#include <windows.h>
#include <gdiplus.h>
class Paintable {
	virtual Gdiplus::Color getColor() const = 0;
};