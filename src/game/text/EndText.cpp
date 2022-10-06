#include "EndText.h"
#include "../Game.h"
class Game;
EndText::EndText(RoundStatus statusToShowOn) : statusToShowOn(statusToShowOn)
	//put text in the center
	,pos(Pos::BASE_WIDTH / 2, Pos::BASE_HEIGHT / 2) {
}

void EndText::update() {
	//fade time only needs to update if it's visible
	if (canDraw()) {
		fadeTime++;
		//after it's finished showing, display the new round
		if (fadeTime >= DISPLAY_TIME) {
			//reset fade timer because we don't destroy the object on new round
			fadeTime = 0;
			Game::getInstance().displayRound();
		}
	}
}

bool EndText::canDraw() {
	return !Game::getInstance().inRound && Game::getInstance().status == statusToShowOn;
}
