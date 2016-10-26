#pragma once
#include "vector2.h"
#include "sector.h"
#include "map.h"
#include "entity.h"
class Player : public AbstractEntity {
private:
	const Vector2 FORWARD = Vector2(0, 1);
	const Vector2 BACKWARD = Vector2(0, -1);
	const Vector2 LEFT = Vector2(-1, 0);
	const Vector2 RIGHT = Vector2(1, 0);
public:
	Player();
	void onUpdate();
};