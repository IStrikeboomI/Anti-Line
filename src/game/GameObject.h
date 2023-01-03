#pragma once
#include <windows.h>
#include <gdiplus.h>
#include "Game.h"
class Game;
class GameObject {
	//updates every tick (1 tick = 16ms)
	virtual void update() {};

	//this method should be used only for drawing and needs to be overriden
	virtual void draw(Gdiplus::Graphics& g) {};

	//some objects need to be drawn at certain times (eg. win/loss text)
	//override this if you need to draw at a time that is not during the round
	virtual bool canDraw() { return Game::getInstance().inRound; };

	virtual void onPlayerCollision(Player& p) {};

	virtual bool isPlayerCollided(Player& p) { return false; };
};