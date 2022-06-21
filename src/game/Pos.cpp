#include "Pos.h"
int Pos::screenWidth = BASE_WIDTH;
int Pos::screenHeight = BASE_HEIGHT;
float Pos::scaleFactorX = (float)screenWidth / BASE_WIDTH;
float Pos::scaleFactorY = (float)screenHeight / BASE_HEIGHT;
std::vector<Pos*> Pos::instances;

void Pos::update(int width, int height) {
	//make sure our dimensions are valid by being positive
	if (width >= 0 && height >= 0) {
		//set all the values
		screenWidth = width;
		screenHeight = height;
		scaleFactorX = (float)screenWidth / BASE_WIDTH;
		scaleFactorY = (float)screenHeight / BASE_HEIGHT;
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

float Pos::scaledFontSize(int size) {
	//take average of the scale factors to use on the font size
	float fontScaleFactor = (scaleFactorX + scaleFactorY) / 2.0f;
	return size * fontScaleFactor;
}

void Pos::clearInstances() {
	instances.clear();
}

Pos::Pos(int x, int y, int width, int height) : x(x), y(y), width(width), height(height),
												scaledX(x), scaledY(y),scaledWidth(width),scaledHeight(height) {
	instances.push_back(this);
}

Pos::~Pos() {
	std::vector<Pos*>::iterator iterator = std::find(instances.begin(), instances.end(), this);
	if (iterator != instances.end()) {
		instances.erase(iterator);
	}
}

void Pos::setX(int x) {
	//these two if statements make sure they're in bounds
	if (x < 0) {
		x = 0;
	}
	if (x > BASE_WIDTH - width) {
		x = BASE_WIDTH - width;
	}
	this->x = x;
	update();
}

void Pos::setY(int y) {
	//these two if statements make sure they're in bounds
	if (y < 0) {
		y = 0;
	}
	if (y > BASE_HEIGHT - height) {
		y = BASE_HEIGHT - height;
	}
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

int Pos::getX() const {
	return x;
}

int Pos::getY() const {
	return y;
}

int Pos::getWidth() const {
	return width;
}

int Pos::getHeight() const {
	return height;
}

bool Pos::isCollided(const Pos& pos, int extraSpace) const {
	return x < pos.x + pos.width + extraSpace && x + width > pos.x + extraSpace  && y < pos.y + pos.height + extraSpace && y + height > pos.y + extraSpace;
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

Pos operator+(const Pos& pos1, const Pos& pos2) {
	return Pos(pos1.x + pos2.x, pos1.y + pos2.y);
}

Pos operator-(const Pos& pos1, const Pos& pos2) {
	return Pos(pos1.x - pos2.x, pos1.y - pos2.y);
}


Pos& Pos::operator+=(const Pos& pos) {
	x += pos.x;
	y += pos.y;
	return *this;
}

Pos& Pos::operator-=(const Pos& pos) {
	x -= pos.x;
	y -= pos.y;
	return *this;
}