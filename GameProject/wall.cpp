#include "wall.h"
Wall::Wall(Vector2 vertex1, Vector2 vertex2) {
	position[0] = vertex1;
	position[1] = vertex2;
	sector = 0;
}

Wall::Wall(const Vector2 vertex1, const Vector2 vertex2, Color color, Sector* sector) {
	position[0] = vertex1;
	position[1] = vertex2;
	this->sector = sector;
	this->color = color;
}

Wall::Wall(const Wall* w) {
	position[0] = w->position[0];
	position[1] = w->position[1];
	sector = w->sector;
}

Vector2* Wall::getPoints() {
	return position;
}

Sector* Wall::getLinkedSector() {
	return sector;
}

Color& Wall::getColor() {
	return color;
}