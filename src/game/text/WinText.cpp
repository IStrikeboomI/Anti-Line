#include "WinText.h"
#include "../Game.h"
class Game;
WinText::WinText() :
    //put text in the center
    pos(Pos::BASE_WIDTH / 2, Pos::BASE_HEIGHT / 2) {
}

void WinText::update() {
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

bool WinText::canDraw() {
    return !Game::getInstance().inRound && Game::getInstance().status == RoundStatus::WON;
}

void WinText::draw(Gdiplus::Graphics& g) const {
    std::wstring winString(L"You Won!");
    Gdiplus::Font font(L"Arial", Pos::scaledFontSize(108));
    Gdiplus::SolidBrush lostBrush(Gdiplus::Color(
        //show opacity as a percent of how much done it is
        ((float)fadeTime / DISPLAY_TIME) * 0xFF, 
        84, 232, 88));

    //this will measure how big the string will be so we can truly center it
    Gdiplus::RectF rect;
    g.MeasureString(winString.c_str(), -1, &font, Gdiplus::PointF(pos.scaledX, pos.scaledY), &rect);

    g.DrawString(winString.c_str(), -1, &font, Gdiplus::PointF(Pos::BASE_WIDTH / 2 - rect.Width / 2, Pos::BASE_HEIGHT / 2 - rect.Height / 2), &lostBrush);

}
