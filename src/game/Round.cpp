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
			//50% chance to swap variables around to add variety to the generated lines so they all don't generate in the same direction
			bool swap = Util::random(0, 1) == 0;
			if (swap) {
				//use a xor swap
				x1 = x1 ^ x2;
				x2 = x1 ^ x2;
				x1 = x1 ^ x2;
				//don't swap y values or else the lines are the same as without the swap
			}
			l = std::make_shared<Line>(x1, y1, x2, y2);
		} while (path.isLineNear(*l,10));
		lines.push_back(l);
	}

}

void Round::update() {
	//update and check if player has collided for all game objects
	for (int i = 0; i < Game::getInstance().gameObjects.size();i++) {
		GameObject& g = Game::getInstance().gameObjects.at(i);
		g.update();
		if (g.isPlayerCollided(player)) {
			g.onPlayerCollision(player);
		}
	}
}

