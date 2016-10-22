#pragma once
#include "vector2.h"
class Player {
private:
	Vector2 position;
	float height;
	float angle;
	float cosAngle;
	float sinAngle;
public:
	Vector2& getPosition();
	float getHeight();
	float getAngle();
	float getCosAngle();
	float getSinAngle();
	void update();
};