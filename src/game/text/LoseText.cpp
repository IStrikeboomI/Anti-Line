#include "LoseText.h"
LoseText::LoseText() : EndText(RoundStatus::LOST) {}

void LoseText::draw(Gdiplus::Graphics& g) const {
    std::wstring lostString(L"You Lost!");
    Gdiplus::Font font(L"Arial", Pos::scaledFontSize(108));
    Gdiplus::SolidBrush lostBrush(Gdiplus::Color(
        //show opacity as a percent of how much done it is
        ((float)fadeTime / DISPLAY_TIME) * 0xFF
        , 240, 58, 58));

    //this will measure how big the string will be so we can truly center it
    Gdiplus::RectF rect;
    g.MeasureString(lostString.c_str(), -1, &font, Gdiplus::PointF(pos.scaledX, pos.scaledY), &rect);

    g.DrawString(lostString.c_str(), -1, &font, Gdiplus::PointF(rect.X - rect.Width / 2, rect.Y - rect.Height / 2), &lostBrush);
}
