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
	Wall(const Vector2& vertex1, const Vector2& vertex2, Sector* sector);
	Wall(const Wall* w);

	Vector2* getPoints();

	Sector* getLinkedSector();
};