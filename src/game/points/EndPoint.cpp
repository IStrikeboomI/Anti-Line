#include "EndPoint.h"
#include "../Game.h"
class Game;
EndPoint::EndPoint() : Point(Util::random(SIDE_LENGTH + 730, SIDE_LENGTH + 820), Util::random(SIDE_LENGTH, 540 - SIDE_LENGTH)) {

}

void EndPoint::onPlayerCollide(Player& p) {
	Game::getInstance().win();
}

void EndPoint::draw(Gdiplus::Graphics& g) const {
	Gdiplus::SolidBrush endingPointBrush(Gdiplus::Color::Red);
	g.FillRectangle(&endingPointBrush, pos.scaledX, pos.scaledY,
						   pos.scaledWidth, pos.scaledHeight);
}
