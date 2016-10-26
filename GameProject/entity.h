#pragma once
#include "vector2.h"
#include "map.h"
#include "sector.h"
class AbstractEntity {
private:
	Vector2 position;
	float angle;
	float cos_angle;
	float sin_angle;
	float move_speed;
	float rot_speed;
	float height;
	Map* map = 0;
	Sector* current_sector = 0;

	void fullSectorSearch();
	void updateRotation();
protected:
	virtual void onUpdate() = 0;
public:
	void update();
	Map* getMap();
	void setMap(Map* game);
	void rotate(float angle);
	void move(const Vector2& dir);
	void moveRelative(const Vector2& relative_dir);
	float getAngle();
	void setAngle(float angle);
	float getCosAngle();
	float getSinAngle();
	float getMoveSpeed();
	void setMoveSpeed(float move_speed);
	float getRotSpeed();
	void setRotSpeed(float rot_speed);
	Sector* getCurrentSector();
	Vector2 getPosition(); //copy vector so no external changes
	void setPosition(const Vector2& vec);
	float getHeight();
	void setHeight(float height);
};