#pragma once
#include "vector2.h"
#include "sector.h"
#include "color.h"
class Sector; //forward declare class to deal with circular include

class Wall {
private:
	Vector2 position[2];
	Sector* sector = 0;
	Color color;
public:
	Wall(Vector2 vertex1, Vector2 vertex2);
	Wall(const Vector2 vertex1, const Vector2 vertex2, Color color, Sector* sector);
	Wall(const Wall* w);

	Vector2* getPoints();

	Sector* getLinkedSector();

	Color& getColor();
};