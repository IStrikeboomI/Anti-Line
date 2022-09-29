#pragma once
//an interface used when a game object needs to update every tick (1 tick = 16ms)
//needs to be registered in the Game class
class ITickable {
public:
	virtual void update() = 0;
};