#pragma once
#include "vector2.h"
#include "sector.h"
#include "map.h"
class Player {
private:
	Vector2 position;
	float height;
	float angle;
	float cosAngle;
	float sinAngle;
	float speed;
	float turn_speed;
	Sector* current_sector;

	void fullSectorSearch(Map& map);
public:
	Player();
	Vector2& getPosition();
	float getHeight();
	float getAngle();
	float getCosAngle();
	float getSinAngle();
	Sector* getCurrentSector();
	void update(Map& map);
	void move(const Vector2& dir);
	void moveRelative(const Vector2& rel_dir);
};