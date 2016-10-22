#include "sector.h"

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

Sector::Sector(float floor, float ceil, Color floor_color, Color ceil_color) {
	this->floor_height = floor;
	this->ceil_height = ceil;
	this->floorColor = floor_color;
	this->ceilColor = ceil_color;
}

Color& Sector::getFloorColor() {
	return floorColor;
}

Color& Sector::getCeilColor() {
	return ceilColor;
}