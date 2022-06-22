#include "EndPoint.h"

EndPoint::EndPoint() : Point(Util::random(SIDE_LENGTH + 730, SIDE_LENGTH + 820), Util::random(SIDE_LENGTH, 540 - SIDE_LENGTH)) {

}

void EndPoint::onPlayerCollide(Player p) {
}

Gdiplus::Color EndPoint::getColor() const {
	return Gdiplus::Color::Red;
}
