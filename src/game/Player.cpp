#include "Player.h"
Player::Player() : pos(0, 0, SIDE_LENGTH, SIDE_LENGTH) {}

//when moving up we need to lower the velocity
void Player::moveUp() {
	yAxisAcceleration += ACCELERATION_INCREASE_AMOUNT;
	yAxisVelocity -= yAxisAcceleration;
}
//when moving down we need to increse the velocity
void Player::moveDown() {
	yAxisAcceleration += ACCELERATION_INCREASE_AMOUNT;
	yAxisVelocity += yAxisAcceleration;
}
//when moving left we need to lower the velocity
void Player::moveLeft() {
	xAxisAcceleration += ACCELERATION_INCREASE_AMOUNT;
	xAxisVelocity -= xAxisAcceleration;
}
//when moving right we need to increse the velocity
void Player::moveRight() {
	xAxisAcceleration += ACCELERATION_INCREASE_AMOUNT;
	xAxisVelocity += xAxisAcceleration;
}

//used for movement, both X and Y axis are the same thing, just different variables
void Player::update() {
	//since acceleration gets added every time we move, we need to cap it
	if (yAxisAcceleration > MAX_ACCELERATION) {
		yAxisAcceleration = MAX_ACCELERATION;
	}
	//this lowers the acceleration so we don't keep moving
	//>= 0.1 so we can actually lower the acceleration when we are supposed to
	if (yAxisAcceleration >= 0.1) {
		yAxisAcceleration -= .1;
		//due to floating point errors we need to round down to 0 when its below .1
		if (yAxisAcceleration <= 0.1) {
			yAxisAcceleration = 0;
		}
	}
	//since velocity gets added every time we move, we need to cap it
	//velocity here can be positive or negative which that determines the direction
	//we use abs so we don't need two separate if statements to do the same thing
	if (std::abs(yAxisVelocity) > MAX_VELOCITY) {
		//using signum to account for the abs
		yAxisVelocity = Util::signum(yAxisVelocity) * MAX_VELOCITY;
	}
	//this brings the velocity to 0 so we don't keep moving
	//using abs for the same reason as above
	if (std::abs(yAxisVelocity) > 0) {
		//using signum to account for the abs
		yAxisVelocity -= Util::signum(yAxisVelocity) * ACCELERATION_INCREASE_AMOUNT / 4;
		//due to floating point errors we need to round down to 0 when its below .15
		if (std::abs(yAxisVelocity) <= 0.15) {
			yAxisVelocity = 0;
		}
	}
	//set the position to add the velocity
	if (yAxisVelocity != 0) {
		int newY = pos.getY() + yAxisVelocity;
		//clamp variables so player doesn't go out of bounds
		if (newY <= 0) {
			pos.setY(0);
		} else if (newY >= Pos::BASE_HEIGHT - pos.getHeight()) {
			pos.setY(Pos::BASE_HEIGHT - pos.getHeight());
		} else {
			pos.setY(newY);
		}
	}

	//since acceleration gets added every time we move, we need to cap it
	if (xAxisAcceleration > MAX_ACCELERATION) {
		xAxisAcceleration = MAX_ACCELERATION;
	}
	//this lowers the acceleration so we don't keep moving
	//>= 0.1 so we can actually lower the acceleration when we are supposed to
	if (xAxisAcceleration >= 0.1) {
		xAxisAcceleration -= .1;
		//due to floating point errors we need to round down to 0 when its below .1
		if (xAxisAcceleration <= 0.1) {
			xAxisAcceleration = 0;
		}
	}
	//since velocity gets added every time we move, we need to cap it
	//velocity here can be positive or negative which that determines the direction
	//we use abs so we don't need two separate if statements to do the same thing
	if (std::abs(xAxisVelocity) > MAX_VELOCITY) {
		//using signum to account for the abs
		xAxisVelocity = Util::signum(xAxisVelocity) * MAX_VELOCITY;
	}
	//this brings the velocity to 0 so we don't keep moving
	//using abs for the same reason as above
	if (std::abs(xAxisVelocity) > 0) {
		//using signum to account for the abs
		xAxisVelocity -= Util::signum(xAxisVelocity) * ACCELERATION_INCREASE_AMOUNT / 4;
		//due to floating point errors we need to round down to 0 when its below .15
		if (std::abs(xAxisVelocity) <= 0.15) {
			xAxisVelocity = 0;
		}
	}

	//set the position to add the velocity
	if (xAxisVelocity != 0) {
		int newX = pos.getX() + xAxisVelocity;
		//clamp variables so player doesn't go out of bounds
		if (newX <= 0) {
			pos.setX(0);
		} else if (newX >= Pos::BASE_WIDTH - pos.getWidth()) {
			pos.setX(Pos::BASE_WIDTH - pos.getWidth());
		} else {
			pos.setX(newX);
		}
	}
	
}

void Player::draw(Gdiplus::Graphics& g) const {
	Gdiplus::SolidBrush playerBrush(argb);
	g.FillRectangle(&playerBrush, pos.scaledX, pos.scaledY,
						   pos.scaledWidth, pos.scaledHeight);

}


