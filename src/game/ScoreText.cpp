#include "ScoreText.h"
#include "Game.h"
class Game;
ScoreText::ScoreText() {
}

void ScoreText::draw(Gdiplus::Graphics& g) const {
    std::wstring scoreString(L"Score: ");
    scoreString += std::to_wstring(Game::getInstance().score);
    Gdiplus::Font font(L"Arial", Pos::scaledFontSize(48));
    Gdiplus::SolidBrush scoreBrush(Gdiplus::Color(132, 135, 135));

    g.DrawString(scoreString.c_str(), -1, &font, Gdiplus::PointF(0, 0), &scoreBrush);
}
