#include "StartPoint.h"

StartPoint::StartPoint() : Point(Util::random(SIDE_LENGTH, SIDE_LENGTH + 50), Util::random(SIDE_LENGTH + 50, 540 - SIDE_LENGTH)) {
	
}

Gdiplus::Color StartPoint::getColor() const {
	return Gdiplus::Color::Lime;
}
