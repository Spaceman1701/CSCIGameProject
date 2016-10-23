#pragma once
#include "vector2.h"
class Wall {
private:
	Vector2 position[2];
	Vector2 height;
	
public:
	Wall(Vector2 vertex1, Vector2 vertex2, float lower, float upper);

	Vector2* getPoints();
	Vector2& getHeight();
};