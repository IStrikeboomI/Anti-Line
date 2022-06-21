#include "Line.h"

Line::Line(int x1, int y1, int x2, int y2) : startPos(x1,y1), endPos(x2, y2) {

}

Gdiplus::Color Line::getColor() const {
	return Gdiplus::Color::Black;
}

//this is basically code i took from stack overflow and just changed the variables around
bool Line::doLinesIntersect(const Line& l) const {
    float p0_x = l.startPos.getX(); 
    float p0_y = l.startPos.getY();
    float p1_x = l.endPos.getX(); 
    float p1_y = l.endPos.getY();

    float p2_x = startPos.getX(); 
    float p2_y = startPos.getY();
    float p3_x = endPos.getX(); 
    float p3_y = endPos.getY();

    float s1_x = p1_x - p0_x;     
    float s1_y = p1_y - p0_y;
    float s2_x = p3_x - p2_x;     
    float s2_y = p3_y - p2_y;

    float s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    float t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    //intersect found
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
        return true;
    }

    return false;
}

