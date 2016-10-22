#pragma once
#include "wall.h"
#include <vector>
#include "color.h"
class Sector {
private:
	std::vector<Wall*> walls;
	float floor_height;
	float ceil_height;
	Color floorColor;
	Color ceilColor;
public:
	std::vector<Wall*>& getWalls();

	void addWall(Wall* wall);

	float getFloorHeight();
	float getCeilHeight();

	Color& getFloorColor();
	Color& getCeilColor();

	Sector(float floor, float ceil, Color floorColor, Color ceilColor);
};