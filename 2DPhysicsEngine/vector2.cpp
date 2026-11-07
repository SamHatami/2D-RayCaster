#include "Vector2.h"
#include <cmath>

//Instance methods

vector2 vector2::Normalized() const
{
	float mag = Magnitude();
	return {x / mag, y / mag};
}

vector2 vector2::GetNormal(vector2& a)
{
	return {-1 * a.y, a.x};

	// x' = x cos(t) - y sin(t)
	// y' = x sin(t) + y cos(t)
}

float vector2::Magnitude() const
{
	return sqrt(x * x + y * y);
}

//Static methods

float vector2::Dot(vector2& a, vector2& b)
{
	return (a.x * b.x + a.y * b.y);
}

float vector2::Dot(const vector2& a, const vector2& b)
{
	return (a.x * b.x + a.y * b.y);
}

float vector2::Magnitude(vector2& a)
{
	return sqrt(a.x * a.x + a.y * a.y);
}

void vector2::Normalize(vector2& a)
{
	float mag = Magnitude(a);
	a.x /= mag;
	a.y /= mag;
}

vector2 operator+(const vector2& a, const vector2& b)
{
	return {a.x + b.x, a.y + b.y};
}

vector2 operator-(const vector2& a, const vector2& b)
{
	return {a.x - b.x, a.y - b.y};
}

vector2 operator*(const vector2& a, float scalar)
{
	return {a.x * scalar, a.y * scalar};
}

vector2 operator/(const vector2& a, float scalar)
{
	return {a.x / scalar, a.y / scalar};
}