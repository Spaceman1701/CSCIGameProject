#pragma once
#include "vector2.h"
float clampf(float v, float min, float max);

bool lineIntersect(Vector2& l1s, Vector2& l1e, Vector2& l2s, Vector2& l2e, Vector2& result);

float signedTriArea(const Vector2& a, const Vector2& b, const Vector2& c); //from "Real Time Collision Detection"

bool qLineIntersect(Vector2& l1s, Vector2& l1e, Vector2& l2s, Vector2& l2e, Vector2& result);

inline float lerp2(float x0, float x1, float y0, float y1, float x) {
	return y0 + (x - x0)*(y1 - y0) / (x1 - x0);
}
