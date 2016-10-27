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

int pointInsideSector(Sector* s, Vector2& point) {
	std::vector<Wall*> walls = s->getWalls();
	for (Wall* w : walls) {
		Vector2 a = w->getPoints()[0];
		Vector2 b = w->getPoints()[1];

		Vector2 dif = b - a;
		Vector2 pDif = point - a;
		float result = dif.vectorPoduct(pDif);
		if (result == 0) {
			return -1;
		}
		if (result > 0) {
			return 0;
		}
	}
	return 1;
}

