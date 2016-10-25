#include "vector2.h"
#include <math.h>
Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}
Vector2::Vector2(const Vector2* vec) {
	x = vec->x;
	y = vec->y;
}

Vector2::Vector2() : Vector2(0.0f, 0.0f){

}

float Vector2::mag() const{
	float sqMag = mag2();
	if (sqMag == 1.0f) {
		return sqMag;
	}
	return sqrtf(sqMag);
}

float Vector2::mag2() const{
	return x*x + y*y;
}

void Vector2::normSelf() {
	float vecMag = mag();
	if (vecMag == 1.0f) { //suprisingly, these early out's improve performance on the vm substaintally
		return;
	}
	x /= vecMag;
	y /= vecMag;
}
Vector2 Vector2::norm() const{
	Vector2 copy(this);
	copy.normSelf();
	return copy;
}

float Vector2::angleTo(Vector2& other) {
	return acosf(other*(*this));
}