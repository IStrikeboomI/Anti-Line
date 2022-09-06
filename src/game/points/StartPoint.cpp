#include "StartPoint.h"

//generate somewhere on the left side
StartPoint::StartPoint() : Point(Util::random(SIDE_LENGTH, SIDE_LENGTH + 50), Util::random(SIDE_LENGTH + 50, 540 - SIDE_LENGTH)) {
	
}

void StartPoint::draw(Gdiplus::Graphics& g) const {
	Gdiplus::SolidBrush startingPointBrush(Gdiplus::Color::Lime);
	g.FillRectangle(&startingPointBrush, pos.scaledX, pos.scaledY,
						   pos.scaledWidth, pos.scaledHeight);

}


