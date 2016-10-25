#pragma once
#include "vector2.h"
#include "sector.h"
class Sector; //forward declare class to deal with circular include

class Wall {
private:
	Vector2 position[2];
	Sector* sector;
public:
	Wall(Vector2 vertex1, Vector2 vertex2);

	Vector2* getPoints();
};