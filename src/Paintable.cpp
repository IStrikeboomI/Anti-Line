#include "Paintable.h"
#include "game/Game.h"
class Game;
bool Paintable::canDraw() {
	return Game::getInstance().inRound;
}