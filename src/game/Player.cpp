#include "Player.h"

Player::Player() : pos(0,0,SIDE_LENGTH, SIDE_LENGTH) {
}

void Player::moveUp() {
	yAxisAcceleration += .2;
	yAxisVelocity -= yAxisAcceleration;
}

void Player::moveDown() {
	yAxisAcceleration += .2;
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
	if (yAxisAcceleration >= 0.1) {
		yAxisAcceleration -= .1;
	}
	if (std::abs(yAxisVelocity) > MAX_VELOCITY) {
		yAxisVelocity = Util::signum(yAxisVelocity) * MAX_VELOCITY;
	}
	if (std::abs(yAxisVelocity) > 0) {
		yAxisVelocity -= Util::signum(yAxisVelocity) * .1;
	}
	pos.setY(pos.getY() + yAxisVelocity);
	std::cout << yAxisAcceleration << "\n" << yAxisVelocity << "\n\n";
}

Gdiplus::Color Player::getColor() const {
	return Gdiplus::Color(argb);
}


