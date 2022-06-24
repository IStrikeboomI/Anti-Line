#include "EndPoint.h"
#include "../Game.h"
class Game;
EndPoint::EndPoint() : Point(Util::random(SIDE_LENGTH + 730, SIDE_LENGTH + 820), Util::random(SIDE_LENGTH, 540 - SIDE_LENGTH)) {

}

void EndPoint::onPlayerCollide(Player p) {
	Game::getInstance().win();
}

Gdiplus::Color EndPoint::getColor() const {
	return Gdiplus::Color::Red;
}
