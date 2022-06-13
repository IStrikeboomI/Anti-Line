#include "Line.h"

Line::Line(int x1, int y1, int x2, int y2) : startPos(x1,y1), endPos(x2, y2) {

}

Gdiplus::Color Line::getColor() const {
	return Gdiplus::Color::Black;
}
