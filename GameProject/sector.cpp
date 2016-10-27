#include "sector.h"
#include <iostream>
std::vector<Wall*>& Sector::getWalls() {
	return walls;
}

void Sector::addWall(Wall* wall) {
	walls.push_back(wall);
}

float Sector::getFloorHeight() {
	return floor_height;
}
float Sector::getCeilHeight() {
	return ceil_height;
}

Sector::Sector(float floor, float ceil, Color floor_color, Color ceil_color, Color floor_step_color, Color ceil_step_color, Color light_level) {
	this->floor_height = floor;
	this->ceil_height = ceil;
	this->floorColor = floor_color;
	this->ceilColor = ceil_color;
	this->floor_step_color = floor_step_color;
	this->ceil_step_color = ceil_step_color;
	this->light_level = light_level;
}

Color& Sector::getFloorColor() {
	return floorColor;
}

Color& Sector::getCeilColor() {
	return ceilColor;
}

Color& Sector::getFloorStepColor() {
	return floor_step_color;
}
Color& Sector::getCeilStepColor() {
	return ceil_step_color;
}

void Sector::setSectorNum(int n) {
	sector_num = n;
}
int Sector::getSectorNum() {
	return sector_num;
}

Color& Sector::getLightLevel() {
	return light_level;
}

Sector::~Sector() {
	std::cout << "sector delete! " << std::endl;
	for (Wall* w : walls) {
		delete w;
	}
}