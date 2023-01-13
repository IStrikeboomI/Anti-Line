#include "GameObject.h"
#include "Game.h"
bool GameObject::canDraw()
{
    return Game::getInstance().inRound;
}
