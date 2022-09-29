#include "LoseText.h"
#include "../Game.h"
class Game;
LoseText::LoseText() :
    //put text in the center
    pos(Pos::BASE_WIDTH/2,Pos::BASE_HEIGHT/2) {
}

void LoseText::update() {
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

bool LoseText::canDraw() {
	return !Game::getInstance().inRound && Game::getInstance().status == RoundStatus::LOST;
}

void LoseText::draw(Gdiplus::Graphics& g) const {
    std::wstring lostString(L"You Lost!");
    Gdiplus::Font font(L"Arial", Pos::scaledFontSize(108));
    Gdiplus::SolidBrush lostBrush(Gdiplus::Color(
        //show opacity as a percent of how much done it is
        ((float)fadeTime / DISPLAY_TIME)*0xFF
        , 240, 58, 58));

    //this will measure how big the string will be so we can truly center it
    Gdiplus::RectF rect;
    g.MeasureString(lostString.c_str(), -1, &font, Gdiplus::PointF(pos.scaledX, pos.scaledY), &rect);

    g.DrawString(lostString.c_str(), -1, &font, Gdiplus::PointF(Pos::BASE_WIDTH / 2 - rect.Width / 2, Pos::BASE_HEIGHT / 2 - rect.Height / 2), &lostBrush);

}
