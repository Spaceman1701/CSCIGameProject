#include "vector2.h"
#include <math.h>
Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}
Vector2::Vector2(Vector2* vec) {
	x = vec->x;
	y = vec->y;
}

float Vector2::mag() {
	float sqMag = mag2();
	if (sqMag == 1.0f) {
		return sqMag;
	}
	return sqrtf(sqMag);
}

float Vector2::mag2() {
	return x*x + y*y;
}

float Vector2::angleTo(Vector2& other) {
	return acosf(other*(*this));
}