#include "player.h"
#include <math.h>
#include "context.h"
#include <SDL2/SDL_keycode.h>

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
	//angle += 0.001f;
	Context* c = Context::getInstance();
	if (c->isKeyDown(SDLK_w)) {
		move(Vector2(0.0f, 0.001f));
	}
	if (c->isKeyDown(SDLK_s)) {
		move(Vector2(0.0f, -0.001f));
	}
	if (c->isKeyDown(SDLK_a)) {
		move(Vector2(0.001f, 0.00f));
	}
	if (c->isKeyDown(SDLK_d)) {
		move(Vector2(-0.001f, 0.00f));
	}
	if (c->isKeyDown(SDLK_LEFT)) {
		angle += 0.01f;
	}
	if (c->isKeyDown(SDLK_RIGHT)) {
		angle -= 0.01f;
	}

	sinAngle = sinf(angle);
	cosAngle = cosf(angle);
}

void Player::move(const Vector2& dir) {
	position.x += dir.x * 10000;
	position.y += dir.y * 100;
}
