#pragma once
#include "vector2.h"
class Player {
private:
	Vector2 position;
	float height;
	float angle;
	float cosAngle;
	float sinAngle;
	float speed;
	float turn_speed;
public:
	Player();
	Vector2& getPosition();
	float getHeight();
	float getAngle();
	float getCosAngle();
	float getSinAngle();
	void update();
	void move(const Vector2& dir);
	void moveRelative(const Vector2& rel_dir);
};