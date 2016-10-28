#include "entity.h"
#include "game_math.h"
#include <math.h>
#include <iostream>
void AbstractEntity::fullSectorSearch() {
	for (Sector* s : map->getSectors()) {
		int pointInside = pointInsideSector(s, position);
		if (pointInside != 0) {
			current_sector = s;
		}
	}
}


void AbstractEntity::updateRotation() {
	if (angle > 2 * (float)M_PI) {
		angle -= 2 * (float)M_PI;
	}
	if (angle < 2 * (float)M_PI) {
		angle += 2 * (float)M_PI;
	}

	sin_angle = sinf(angle);
	cos_angle = cosf(angle);
}


void AbstractEntity::update() {
	if (!current_sector || !pointInsideSector(current_sector, position)) {
		fullSectorSearch();
	}
	updateRotation();
	onUpdate();

}

Map* AbstractEntity::getMap() {
	return map;
}

void AbstractEntity::setMap(Map* map) {
	this->map = map;
}

void AbstractEntity::rotate(float angle) {
	this->angle += angle * rot_speed;
}

void AbstractEntity::move(const Vector2& dir) {
	Vector2 normDir = dir.norm();
	position.x += normDir.x * move_speed;
	position.y += normDir.y * move_speed;
}

void AbstractEntity::moveRelative(const Vector2& relative_dir) {
	Vector2 dir;
	dir.x = cos_angle * relative_dir.x + sin_angle * relative_dir.y;
	dir.y = cos_angle * relative_dir.y - sin_angle * relative_dir.x;
	move(dir);
}

float AbstractEntity::getAngle() {
	return angle;
}

void AbstractEntity::setAngle(float angle) {
	this->angle = angle;
}

float AbstractEntity::getCosAngle() {
	return cos_angle;
}

float AbstractEntity::getSinAngle() {
	return sin_angle;
}

float AbstractEntity::getMoveSpeed() {
	return move_speed;
}

void AbstractEntity::setMoveSpeed(float move_speed) {
	this->move_speed = move_speed;
}

float AbstractEntity::getRotSpeed() {
	return rot_speed;
}

void AbstractEntity::setRotSpeed(float rot_speed) {
	this->rot_speed = rot_speed;
}

Sector* AbstractEntity::getCurrentSector() {
	return current_sector;
}

Vector2 AbstractEntity::getPosition() {
	return position;
}

void AbstractEntity::setPosition(const Vector2& vec) {
	this->position = vec;
}

float AbstractEntity::getHeight() {
	return height;
}

void AbstractEntity::setHeight(float height) {
	this->height = height;
}

int AbstractEntity::insideMap() {
	if (pointInsideSector(current_sector, position)) {
		return 1;
	}
	this->fullSectorSearch();
	if (pointInsideSector(current_sector, position)) {
		return 1;
	}
	return 0;
}

