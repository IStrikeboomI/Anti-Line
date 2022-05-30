#include "Pos.h"
int Pos::screenHeight = 540;
int Pos::screenWidth = 960;
float Pos::scaleFactorX = (float)screenWidth / 960;
float Pos::scaleFactorY = (float)screenHeight / 540;
std::vector<Pos*> Pos::instances;

void Pos::update(int width, int height) {
	//make sure our dimensions are valid by being positive
	if (width >= 0 && height >= 0) {
		//set all the values
		screenWidth = width;
		screenHeight = height;
		scaleFactorX = (float)screenWidth / 960;
		scaleFactorY = (float)screenHeight / 540;
	} else {
		//throw an error if update is called using a negative parameter
		throw std::invalid_argument("Width nor height cannot be less than or equal to 0");
	}

	//loop through each instance and scale the dimensions
	for (Pos* p : instances) {
		p->scaledX = p->x * scaleFactorX;
		p->scaledY = p->y * scaleFactorY;
		p->scaledWidth = p->width * scaleFactorX;
		p->scaledHeight = p->height * scaleFactorY;
	}
}

int Pos::scaledFontSize(int size) {
	//take average of the scale factors to use on the font size
	float fontScaleFactor = (scaleFactorX + scaleFactorY) / 2.0;
	return size * fontScaleFactor;
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

