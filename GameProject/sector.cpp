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

Sector::Sector(float floor, float ceil, Color floor_color, Color ceil_color, Color floor_step_color, Color ceil_step_color) {
	this->floor_height = floor;
	this->ceil_height = ceil;
	this->floorColor = floor_color;
	this->ceilColor = ceil_color;
	this->floor_step_color = floor_step_color;
	this->ceil_step_color = ceil_step_color;
}

Sector::Sector(Sector* s) {
	this->floor_height = s->floor_height;
	this->ceil_height = s->ceil_height;
	this->floorColor = s->floorColor;
	this->ceilColor = s->ceilColor;
	this->floor_step_color = s->floor_step_color;
	this->ceil_step_color = s->ceil_step_color;
	this->walls = s->walls;
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