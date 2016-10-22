#pragma once
#include "wall.h"
#include <vector>
class Sector {
private:
	std::vector<Wall*> walls;
	float floor_height;
	float ceil_height;
public:
	std::vector<Wall*>& getWalls();

	void addWall(Wall* wall);

	float getFloorHeight();
	float getCeilHeight();

	Sector(float floor, float ceil);
};