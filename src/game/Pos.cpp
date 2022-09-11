#include "Pos.h"
int Pos::screenWidth = BASE_WIDTH;
int Pos::screenHeight = BASE_HEIGHT;
double Pos::scaleFactorX = (double)screenWidth / BASE_WIDTH;
double Pos::scaleFactorY = (double)screenHeight / BASE_HEIGHT;
std::vector<Pos*> Pos::instances;

void Pos::updateAll(int width, int height) {
	//make sure our dimensions are valid by being positive
	if (width >= 0 && height >= 0) {
		//set all the values
		screenWidth = width;
		screenHeight = height;
		scaleFactorX = (double)screenWidth / BASE_WIDTH;
		scaleFactorY = (double)screenHeight / BASE_HEIGHT;
	} else {
		//throw an error if update is called using a negative parameter
		throw std::invalid_argument("Width nor height cannot be less than or equal to 0");
	}
	//loop through each instance and scale the dimensions
	for (Pos* p : instances) {
		p->update();
	}
}

void Pos::update() {
	scaledX = x * scaleFactorX;
	scaledY = y * scaleFactorY;
	scaledWidth = width * scaleFactorX;
	scaledHeight = height * scaleFactorY;
}

double Pos::scaledFontSize(int size) {
	//take average of the scale factors to use on the font size
	double fontScaleFactor = (scaleFactorX + scaleFactorY) / 2.0f;
	return size * fontScaleFactor;
}

void Pos::clearInstances() {
	instances.clear();
}

Pos::Pos(int x, int y, int width, int height) : x(x), y(y), width(width), height(height),
												scaledX(x * scaleFactorX), scaledY(y * scaleFactorY),scaledWidth(width * scaleFactorX),scaledHeight(height * scaleFactorY) {
	instances.push_back(this);
}

Pos::~Pos() {
	//find location of the pos
	std::vector<Pos*>::iterator iterator = std::find(instances.begin(), instances.end(), this);
	//check if it exists
	if (iterator != instances.end()) {
		instances.erase(iterator);
	}
}

void Pos::setX(int x) {
	//these two if statements make sure they're in bounds
	if (x < 0) {
		throw std::invalid_argument("x position should be above 0, got " + y);
	}
	if (x > BASE_WIDTH - width) {
		throw std::invalid_argument(std::string("x position should be below ").append("" + BASE_WIDTH - width).append(" ,got ").append("" + x));
	}
	this->x = x;
	update();
}

void Pos::setY(int y) {
	//these two if statements make sure they're in bounds
	if (y < 0) {
		throw std::invalid_argument("y position should be above 0, got " + y);
	}
	if (y > BASE_HEIGHT - height) {
		throw std::invalid_argument(std::string("y position should be below ").append("" + BASE_HEIGHT - height).append(" ,got ").append("" + y));
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

double Pos::getDistanceTo(const Pos& pos) const {
	//the distance formula
	int xDistance = x - pos.getX();
	int yDistance = y - pos.getY();
	return std::sqrt(xDistance * xDistance + yDistance * yDistance);
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