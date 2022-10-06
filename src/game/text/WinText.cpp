#include "WinText.h"
WinText::WinText() : EndText(RoundStatus::WON) {}

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
