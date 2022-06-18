#include "Round.h"

Round::Round() : startPoint(), endPoint(), player(), path(startPoint.pos, endPoint.pos) {
	//position player in the center of the starting point
	player.pos.setX(startPoint.pos.getX() + startPoint.pos.getWidth() / 2 - player.pos.getWidth() / 2);
	player.pos.setY(startPoint.pos.getY() + startPoint.pos.getHeight() / 2 - player.pos.getHeight() / 2);

	//generate a random amount (5 to 15) of lines
	for (int i = 0; i < Util::random(15, 25);i++) {
		//these are random numbers I pulled out of nowhere
		int x1 = Util::random(140,600);
		int y1 = Util::random(0, 360);
		int x2 = Util::random(30,270) + x1;
		int y2 = Util::random(120, Pos::BASE_HEIGHT - 360) + y1;
		for (const std::shared_ptr<Line> l : lines) {
			while ((std::abs(x1 - l->startPos.getX()) <= Player::SIDE_LENGTH * 2 
				 && std::abs(x2 - l->endPos.getX()) <= Player::SIDE_LENGTH * 2)) {
				x1 = Util::random(140, 600);
				x2 = Util::random(30, 270) + x1;
			}
			while ((std::abs(y1 - l->startPos.getY()) <= Player::SIDE_LENGTH * 4
					&& std::abs(y2 - l->endPos.getY()) <= Player::SIDE_LENGTH * 4)) {
				y1 = Util::random(0, 360);
				y2 = Util::random(120, Pos::BASE_HEIGHT - 360) + y1;
			}
		}
		lines.push_back(std::make_shared<Line>(x1, y1, x2, y2));
	}
}

void Round::update() {
	player.update();
}

void Round::win() {

}

void Round::lose() {

}
