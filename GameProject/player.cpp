#include "player.h"
#include <math.h>

Vector2& Player::getPosition() {
	return position;
}
float Player::getHeight() {
	return height;
}

float Player::getAngle() {
	return angle;
}

float Player::getCosAngle() {
	return cosAngle;
}

float Player::getSinAngle() {
	return sinAngle;
}

void Player::update() {
	angle += 0.001f;
	sinAngle = sinf(angle);
	cosAngle = cosf(angle);
}