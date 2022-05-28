#include "Pos.h"
int Pos::screenHeight = 540;
int Pos::screenWidth = 960;
std::vector<Pos*> Pos::instances;

void Pos::update(int width, int height) {
	screenWidth = width;
	screenHeight = height;

	//These two floats are used for scaling the pos
	//a scale factor of 1 is for a 960x540 window
	float scaleFactorX = (float) screenWidth / 960;
	float scaleFactorY = (float) screenHeight / 540;

	for (Pos* p : instances) {
		p->scaledX = p->x * scaleFactorX;
		p->scaledY = p->y * scaleFactorY;
		p->scaledWidth = p->width * scaleFactorX;
		p->scaledHeight = p->height * scaleFactorY;
	}
}

void Pos::clearInstances() {
	instances.clear();
}

Pos::Pos(int x, int y, int width, int height) : x(x), y(y), width(width), height(height),
												scaledX(x), scaledY(y),scaledWidth(width),scaledHeight(height) {
	instances.push_back(this);
}

void Pos::setX(int x) {
	this->x = x;
	update();
}

void Pos::setY(int y) {
	this->y = y;
	update();
}

void Pos::setWidth(int width) {
	this->width = width;
	update();
}

void Pos::setHeight(int height) {
	this->height = height;
	update();
}

std::ostream& operator<<(std::ostream& os, const Pos& pos) {
	os << "Pos["
		<< "x = " << pos.x
		<< ", y = " << pos.y
		<< ", width = " << pos.width
		<< ", height = " << pos.height
		<< ", scaledX = " << pos.scaledX
		<< ", scaledY = " << pos.scaledY
		<< ", scaledWidth = " << pos.scaledWidth
		<< ", scaledHeight = " << pos.scaledHeight
		<< "]";
	return os;
}

bool operator==(const Pos& pos1, const Pos& pos2) {
	return pos1.x == pos2.x
		&& pos1.y == pos2.y
		&& pos1.width == pos2.width
		&& pos1.height == pos2.height;
}

bool operator!=(const Pos& pos1, const Pos& pos2) {
	return pos1.x != pos2.x
		&& pos1.y != pos2.y
		&& pos1.width != pos2.width
		&& pos1.height != pos2.height;
}

