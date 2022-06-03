#include "Player.h"

Player::Player() : pos(0,0,SIDE_LENGTH, SIDE_LENGTH) {
}

void Player::moveUp(int distance) {
	pos.setY(pos.getY() - distance);
}

void Player::moveDown(int distance) {
	pos.setY(pos.getY() + distance);
}

void Player::moveLeft(int distance) {
	pos.setX(pos.getX() - distance);
}

void Player::moveRight(int distance) {
	pos.setX(pos.getX() + distance);
}

