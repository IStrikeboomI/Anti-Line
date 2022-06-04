#include "EndPoint.h"

EndPoint::EndPoint() : pos(Util::random(SIDE_LENGTH+730, SIDE_LENGTH + 820), Util::random(SIDE_LENGTH, 540 - SIDE_LENGTH), SIDE_LENGTH, SIDE_LENGTH) {

}

Gdiplus::Color EndPoint::getColor() const {
	return Gdiplus::Color(255,0,0);
}
