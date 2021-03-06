#include "Round.h"
#include "Game.h"
class Game;
Round::Round() : startPoint(), endPoint(), player(), path(startPoint.pos, endPoint.pos) {
	//position player in the center of the starting point
	player.pos.setX(startPoint.pos.getX() + startPoint.pos.getWidth() / 2 - player.pos.getWidth() / 2);
	player.pos.setY(startPoint.pos.getY() + startPoint.pos.getHeight() / 2 - player.pos.getHeight() / 2);

	//generate a random amount (5 to 15) of lines
	for (int i = 0; i < Util::random(35, 55);i++) {
		std::shared_ptr<Line> l;
		//keep making new lines if the line is near the path
		do {
			int x1 = Util::random(140, 500);
			int y1 = Util::random(0, 240);
			int x2 = Util::random(130, 270) + x1;
			int y2 = Util::random(240, 540 - 170) + y1;
			l = std::make_shared<Line>(x1, y1, x2, y2);
		} while (path.isLineNear(*l,10));
		lines.push_back(l);
	}

	//update all the positions to make sure the lines are in the correct place
	Pos::update();
}

void Round::update() {
	player.update();
	
	//call the player collision functions if the player collides
	if (player.pos.isCollided(startPoint.pos)) {
		startPoint.onPlayerCollide(player);
	}
	if (player.pos.isCollided(endPoint.pos)) {
		endPoint.onPlayerCollide(player);
	}

	//These 5 variables make 4 lines that represent the outline of the player's cube
	const Pos PLAYER_POS = player.pos;
	Line topX(PLAYER_POS.getX(), PLAYER_POS.getY(), PLAYER_POS.getX() + PLAYER_POS.getWidth(), PLAYER_POS.getY());
	Line bottomX(PLAYER_POS.getX(), PLAYER_POS.getY() + PLAYER_POS.getHeight(), PLAYER_POS.getX() + PLAYER_POS.getWidth(), PLAYER_POS.getY() + PLAYER_POS.getHeight());
	Line leftY(PLAYER_POS.getX(), PLAYER_POS.getY(), PLAYER_POS.getX(), PLAYER_POS.getY() + PLAYER_POS.getHeight());
	Line rightY(PLAYER_POS.getX() + PLAYER_POS.getWidth(), PLAYER_POS.getY(), PLAYER_POS.getX() + PLAYER_POS.getWidth(), PLAYER_POS.getY() + PLAYER_POS.getHeight());

	//loop over all the lines and check if any of the player lines intersect and if they do, LOSE
	for (const std::shared_ptr<Line>& l : lines) {
		if (l->doLinesIntersect(topX) || l->doLinesIntersect(bottomX) || l->doLinesIntersect(leftY) || l->doLinesIntersect(rightY) ) {
			Game::getInstance().lose();
		}
	}
}

