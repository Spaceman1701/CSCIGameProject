#include "wall.h"
Wall::Wall(Vector2 vertex1, Vector2 vertex2) {
	position[0] = vertex1;
	position[1] = vertex2;
	sector = 0;
}

Vector2* Wall::getPoints() {
	return position;
}