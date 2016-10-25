#include "player.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "context.h"
#include <SDL2/SDL_keycode.h>

Player::Player() {
	height = 5;
	speed = 3;
	turn_speed = 0.05f;
}

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
	if (angle > 2 * M_PI) {
		angle -= 2 * (float)M_PI;
	}
	if (angle < 2 * (float)M_PI) {
		angle += 2 * (float)M_PI;
	}

	sinAngle = sinf(angle);
	cosAngle = cosf(angle);

	Context* c = Context::getInstance();
	if (c->isKeyDown(SDLK_w)) {
		moveRelative(Vector2(0, 1));
	}
	if (c->isKeyDown(SDLK_s)) {
		moveRelative(Vector2(0, -1));
	}
	if (c->isKeyDown(SDLK_a)) {
		moveRelative(Vector2(-1, 0));
	}
	if (c->isKeyDown(SDLK_d)) {
		moveRelative(Vector2(1, 0));
	}
	if (c->isKeyDown(SDLK_LEFT)) {
		angle -= turn_speed;
	}
	if (c->isKeyDown(SDLK_RIGHT)) {
		angle += turn_speed;
	}

	
}

void Player::move(const Vector2& dir) {
	Vector2 normDir = dir.norm();
	position.x += normDir.x * speed;
	position.y += normDir.y * speed;
}

void Player::moveRelative(const Vector2& rel_dir) {
	Vector2 dir;
	dir.x = cosAngle * rel_dir.x + sinAngle * rel_dir.y;
	dir.y = cosAngle * rel_dir.y - sinAngle * rel_dir.x;
	move(dir);
}
