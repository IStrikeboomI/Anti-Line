#include "Round.h"

Round::Round() : startPoint(), endPoint(), player() {
	//position player in the center of the starting point
	player.pos.setX(startPoint.pos.getX() + startPoint.pos.getWidth() / 2 - player.pos.getWidth() / 2);
	player.pos.setY(startPoint.pos.getY() + startPoint.pos.getHeight() / 2 - player.pos.getHeight() / 2);

	//generate a random amount (5 to 15) of lines
	for (int i = 0; i < Util::random(5, 15);i++) {
		int x1 = Util::random(100,300);
		
		int x2 = Util::random(30,100) + x1;

		lines.push_back(std::make_shared<Line>(x1,50,x2,70));
	}
}

void Round::update() {
	player.update();
}
