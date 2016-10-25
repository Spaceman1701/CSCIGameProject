#include "game_math.h"
#include "vector2.h"

float clampf(float v, float min, float max) { //probably should just use templates for this
	if (v < min) {
		return min;
	}
	if (v > max) {
		return max;
	}
	return v;
}

int clampi(int v, int min, int max) {
	if (v < min) {
		return min;
	}
	if (v > max) {
		return max;
	}
	return v;
}

bool lineIntersect(Vector2& l1s, Vector2& l1e, Vector2& l2s, Vector2& l2e, Vector2& result) {
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

bool qLineIntersect(Vector2& l1s, Vector2& l1e, Vector2& l2s, Vector2& l2e, Vector2& result) { //only call if you know there is an intersection
	float denominator = (l1s.x - l1e.x)*(l2s.y - l2e.y) - (l1s.y - l1e.y) * (l2s.x - l2e.x);
	if (denominator == 0) {
		return false;
	}
	float xy34 = l2s.x * l2e.y - l2s.y * l2e.x;
	float xy12 = l1s.x * l1e.y - l1s.y * l1e.y;

	float x = xy12 * (l2s.x - l2e.x) - xy34 * (l1s.x - l1e.x);
	float y = xy12 * (l2s.y - l2e.y) - xy34 * (l1s.y - l1e.y);

	x /= denominator;
	y /= denominator;
	result = Vector2(x, y);
	return true;
}

