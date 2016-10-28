#include "player.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "context.h"
#include <SDL2/SDL_keycode.h>
#include "game_math.h"
Player::Player() {
	setMoveSpeed(10.0f);
	setRotSpeed(0.05f);
	setPosition(Vector2(0, 0));
	setAngle(0);
	setHeight(100);
}

void Player::onUpdate() {
	Context* c = Context::getInstance();
	Vector2 pre_move_pos = getPosition();
	if (c->isKeyDown(SDLK_w)) {
		moveRelative(FORWARD);
	}
	if (c->isKeyDown(SDLK_s)) {
		moveRelative(BACKWARD);
	}
	if (c->isKeyDown(SDLK_a)) {
		moveRelative(LEFT);
	}
	if (c->isKeyDown(SDLK_d)) {
		moveRelative(RIGHT);
	}
	if (c->isKeyDown(SDLK_LEFT)) {
		rotate(-1);
	}
	if (c->isKeyDown(SDLK_RIGHT)) {
		rotate(1);
	}
	if (!insideMap()) {
		setPosition(pre_move_pos); //can make walls feel sticky
	}
	setHeight(getCurrentSector()->getFloorHeight() + 100);
}

