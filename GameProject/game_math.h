#pragma once
#include "vector2.h"
#include "sector.h"
float clampf(float v, float min, float max);

int clampi(int v, int min, int max);

bool qLineIntersect(Vector2& l1s, Vector2& l1e, Vector2& l2s, Vector2& l2e, Vector2& result);

inline float lerp2(float x0, float x1, float y0, float y1, float x) { //another function that ought to be templated
	return y0 + (x - x0)*(y1 - y0) / (x1 - x0);
}

inline int lerp2i(int x0, int x1, int y0, int y1, int x) {
	return y0 + (x - x0)*(y1 - y0) / (x1 - x0);
}

bool pointInsideSector(Sector* s, Vector2& point);
