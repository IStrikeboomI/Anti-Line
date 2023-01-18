#include "Line.h"
#include "Game.h"
class Game;
Line::Line(int x1, int y1, int x2, int y2) : startPos(x1,y1), endPos(x2, y2) {

}

void Line::draw(Gdiplus::Graphics& g) const {
    Gdiplus::Pen linePen(Gdiplus::Color::Black);
    g.DrawLine(&linePen, startPos.scaledX, startPos.scaledY, endPos.scaledX, endPos.scaledY);
}


//this is basically code i took from stack overflow and just changed the variables around
bool Line::doLinesIntersect(const Line& l) const {
    double p0_x = l.startPos.getX(); 
    double p0_y = l.startPos.getY();
    double p1_x = l.endPos.getX(); 
    double p1_y = l.endPos.getY();

    double p2_x = startPos.getX(); 
    double p2_y = startPos.getY();
    double p3_x = endPos.getX(); 
    double p3_y = endPos.getY();

    double s1_x = p1_x - p0_x;     
    double s1_y = p1_y - p0_y;
    double s2_x = p3_x - p2_x;     
    double s2_y = p3_y - p2_y;

    double s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    double t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    //intersect found
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
        return true;
    }

    return false;
}

void Line::onPlayerCollision(Player& p){
    Game::getInstance().lose();
}

bool Line::isPlayerCollided(Player& p) {
    //These 5 variables make 4 lines that represent the outline of the player's cube
    const Pos PLAYER_POS = p.pos;
    Line topX(PLAYER_POS.getX(), PLAYER_POS.getY(), PLAYER_POS.getX() + PLAYER_POS.getWidth(), PLAYER_POS.getY());
    Line bottomX(PLAYER_POS.getX(), PLAYER_POS.getY() + PLAYER_POS.getHeight(), PLAYER_POS.getX() + PLAYER_POS.getWidth(), PLAYER_POS.getY() + PLAYER_POS.getHeight());
    Line leftY(PLAYER_POS.getX(), PLAYER_POS.getY(), PLAYER_POS.getX(), PLAYER_POS.getY() + PLAYER_POS.getHeight());
    Line rightY(PLAYER_POS.getX() + PLAYER_POS.getWidth(), PLAYER_POS.getY(), PLAYER_POS.getX() + PLAYER_POS.getWidth(), PLAYER_POS.getY() + PLAYER_POS.getHeight());
    
    //loop over all the lines and check if any of the player lines intersect and if they do, then the player is collided
    return doLinesIntersect(topX) ||
           doLinesIntersect(bottomX) ||
           doLinesIntersect(leftY) ||
           doLinesIntersect(rightY);
}

