#include "Round.h"
#include "Game.h"
#include <iostream>
class Game;
Round::Round() : path(startPoint.pos, endPoint.pos) {
	//position player in the center of the starting point
	player.pos.setX(startPoint.pos.getX() + startPoint.pos.getWidth() / 2 - player.pos.getWidth() / 2);
	player.pos.setY(startPoint.pos.getY() + startPoint.pos.getHeight() / 2 - player.pos.getHeight() / 2);

	//generate a random amount (35 to 55) of lines
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

	registerPaintables();
	registerTickables();
}

void Round::update() {
	for (ITickable& t : tickableObjects) {
		t.update();
	}
	
	//TODO move everything below here to a separate collision handler class
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

Round& Round::operator=(const Round& r) {
	startPoint = r.startPoint;
	endPoint = r.endPoint;
	player = r.player;
	path = r.path;
	lines = r.lines;
	//because we have a vector of refernces, we can't copy them over or else they will be referring to the wrong objects
	//instead we clear both vectors, then re add them to the vectors
	paintableObjects.clear();
	tickableObjects.clear();
	registerPaintables();
	registerTickables();
	return *this;
}

void Round::registerPaintables() {
	paintableObjects.push_back(startPoint);
	paintableObjects.push_back(endPoint);
	paintableObjects.push_back(player);
	paintableObjects.push_back(stopwatch);
	paintableObjects.push_back(scoreText);
	for (std::shared_ptr<Line>& l : lines) {
		paintableObjects.push_back(*l);
	}
}

void Round::registerTickables() {
	tickableObjects.push_back(player);
	tickableObjects.push_back(stopwatch);
}


