#pragma once
#include "game/Player.h"

//an interface that should be used for objects that need to handle something when the player collides with it
//needs to be registered in Game class
class IPlayerCollidable {
public:
	virtual void onPlayerCollision(Player& p) = 0;
};