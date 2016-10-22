#pragma once
#include "vector2.h"
class Wall {
private:
	Vector2 position[2];	
public:
	Wall(Vector2 vertex1, Vector2 vertex2);

	Vector2* getPoints();
};