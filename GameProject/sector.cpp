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

Sector::Sector(float floor, float ceil) {
	this->floor_height = floor;
	this->ceil_height = ceil;
}