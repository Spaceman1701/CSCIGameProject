#pragma once
#include "vector2.h"
#include "sector.h"
#include <math.h>

const float DEGTORAD = (float)(M_PI / 180.0); //multiply by this to get radians
const float RADTODEG = (float)(180.0 / M_PI); //multiply by this to get degrees

float clampf(float v, float min, float max);

int clampi(int v, int min, int max);

bool qLineIntersect(Vector2& l1s, Vector2& l1e, Vector2& l2s, Vector2& l2e, Vector2& result);

inline float lerp2(float x0, float x1, float y0, float y1, float x) { //another function that ought to be templated
	return y0 + (x - x0)*(y1 - y0) / (x1 - x0);
}

inline int lerp2i(int x0, int x1, int y0, int y1, int x) {
	return y0 + (x - x0)*(y1 - y0) / (x1 - x0);
}

int pointInsideSector(Sector* s, Vector2& point);

