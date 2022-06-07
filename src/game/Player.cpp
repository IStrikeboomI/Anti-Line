#include "Player.h"

Player::Player() : pos(0,0,SIDE_LENGTH, SIDE_LENGTH) {
}

void Player::moveUp() {
	yAxisAcceleration += .1;
	yAxisVelocity -= yAxisAcceleration;
}

void Player::moveDown() {
	yAxisAcceleration += .1;
	yAxisVelocity += yAxisAcceleration;
}

void Player::moveLeft() {
	pos.setX(pos.getX() - 5);
}

void Player::moveRight() {
	pos.setX(pos.getX() + 5);
}

void Player::move() {

}

void Player::idle() {
	if (yAxisAcceleration > MAX_ACCELERATION) {
		yAxisAcceleration = MAX_ACCELERATION;
	}
	if (yAxisAcceleration > 0) {
		yAxisAcceleration -= .1;
	}
	if (std::abs(yAxisVelocity) > MAX_VELOCITY) {
		yAxisVelocity = std::signbit(yAxisVelocity) * MAX_VELOCITY;
	}
	if (yAxisVelocity > 0) {
		yAxisVelocity -= std::signbit(yAxisVelocity) * .1;
	}
	pos.setY(pos.getY() + yAxisVelocity);
	std::cout << yAxisAcceleration << "\n" << yAxisVelocity << "\n\n";
}

Gdiplus::Color Player::getColor() const {
	return Gdiplus::Color(argb);
}


