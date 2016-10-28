#pragma once
class Vector2 {
public:
	float x;
	float y;

	Vector2(float x, float y);
	Vector2(const Vector2* vec);
	Vector2();

	float mag() const;
	float mag2() const;

	float angleTo(Vector2& other);

	void normSelf();
	Vector2 norm() const;

	inline float vectorPoduct(const Vector2& other) {
		return x * other.y - other.x * y;
	}

	inline void operator+=(const Vector2& right) {
		x += right.x;
		y += right.y;
	}
};

inline Vector2 operator*(const Vector2& left, float right) {
	return Vector2(left.x * right, left.y * right);
}

inline Vector2 operator*(float left, const Vector2& right) {
	return Vector2(right.x * left, right.y * left);
}

inline Vector2 operator-(const Vector2& left, const Vector2& right) {
	return Vector2(left.x - right.x, left.y - right.y);
}

inline float operator*(const Vector2& left, const Vector2& right) {
	return left.x*right.x + left.y*right.y;
}

inline Vector2 operator+(const Vector2& left, const Vector2& right) {
	return Vector2(left.x + right.x, left.y + right.y);
}

inline Vector2 operator-(const Vector2& vec) {
	return Vector2(-vec.x, -vec.y);
}

inline bool operator==(const Vector2& left, const Vector2& right) {
	return left.x == right.x && left.y == right.y;
}