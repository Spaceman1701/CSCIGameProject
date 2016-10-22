#pragma once
class Vector2 {
public:
	float x;
	float y;

	Vector2(float x, float y);
	Vector2(Vector2* vec);

	Vector2();

	float mag();
	float mag2();

	float angleTo(Vector2& other);

	inline Vector2 operator+(const Vector2& right) {
		return Vector2(right.x + x, right.y + y);
	}

	inline Vector2 operator-(const Vector2& right) {
		return Vector2(x - right.x, y - right.y);
	}

	inline float operator*(const Vector2& right) {
		return x*right.x + y*right.y;
	}

	inline float vectorPoduct(const Vector2& other) {
		return x * other.y - other.x * y;
	}
};

inline Vector2 operator*(const Vector2& left, float right) {
	return Vector2(left.x * right, left.y * right);
}

inline Vector2 operator*(float left, const Vector2& right) {
	return Vector2(right.x * left, right.y * left);
}
