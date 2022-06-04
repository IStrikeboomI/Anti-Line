#include "StartPoint.h"

StartPoint::StartPoint() : pos(Util::random(SIDE_LENGTH, SIDE_LENGTH + 50), Util::random(SIDE_LENGTH + 50, 540 - SIDE_LENGTH), SIDE_LENGTH, SIDE_LENGTH) {
	
}

Gdiplus::Color StartPoint::getColor() const {
	return Gdiplus::Color(0,255,0);
}
