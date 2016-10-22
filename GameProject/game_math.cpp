#include "game_math.h"
#include "vector2.h"

float clampf(float v, float min, float max) {
	if (v < min) {
		return min;
	}
	if (v > max) {
		return max;
	}
	return v;
}

bool lineIntersect(const Vector2& l1s, const Vector2& l1e, const Vector2& l2s, const Vector2& l2e, Vector2& result) {
	float a1 = signedTriArea(l1s, l1e, l2e);
	float a2 = signedTriArea(l1s, l1e, l2s);

	if (a1 * a2 < 0.0f) {
		float a3 = signedTriArea(l2s, l2e, l1s);
		float a4 = a3 * a2 - a1;

		if (a3 * a4 < 0.0f) { //points on different signs = there is an intersection
			float t = a3 / (a3 - a4); //parameter location of intersect
			result = l1s + (t * (l1e - l1s));
			return true;
		}
	}
	return false;
}

float signedTriArea(const Vector2& a, const Vector2& b, const Vector2& c) {
	return (a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x);
}