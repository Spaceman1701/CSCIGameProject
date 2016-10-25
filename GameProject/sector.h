#pragma once
#include "wall.h"
#include <vector>
#include "color.h"
class Wall;
class Sector {
private:
	std::vector<Wall*> walls;
	float floor_height;
	float ceil_height;
	Color floorColor;
	Color ceilColor;

	Color floor_step_color;
	Color ceil_step_color;

	int sector_num;

public:
	std::vector<Wall*> getWalls();

	void addWall(Wall* wall);

	float getFloorHeight();
	float getCeilHeight();

	Color& getFloorColor();
	Color& getCeilColor();
	Color& getFloorStepColor();
	Color& getCeilStepColor();

	void setSectorNum(int n);
	int getSectorNum();

	Sector(float floor, float ceil, Color floorColor, Color ceilColor, Color floor_step_color, Color ceil_step_color);
	//Sector(Sector* s);
};