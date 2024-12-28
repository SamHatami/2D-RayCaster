#include "Vector2.h"
#include <cmath>

//Instance methods
void vector2::Multiply(float scalar)
{
	x *= scalar;
	y *= scalar;
}

void vector2::Divide(float scalar)
{
	if (scalar != 0) {
		x /= scalar;
		y /= scalar;
	}
	else {
		x = 0;
		y = 0;

	}
}

void vector2::Normalize()
{
	float mag = Magnitude();
	x /= mag;
	y /= mag;
}

vector2 vector2::Normalized() const
{
	float mag = Magnitude();
	return { x / mag, y / mag };

}

float vector2::Magnitude() const
{
	return sqrt(x * x + y * y);
}



//Static methods
vector2 vector2::Add(vector2& a, vector2& b)
{
	return {a.x + b.x, a.y + b.y};

}

vector2 vector2::Subtract(vector2& a, vector2& b)
{
	return {a.x - b.x, a.y - b.y};
}

void vector2::Multiply(vector2& a, float scalar)
{
	a.x*=scalar;
	a.y*=scalar;
}

void vector2::Divide(vector2& a, float scalar)
{
	if (scalar != 0) {
		a.x /= scalar;
		a.y /= scalar;
	}
	else {
		a.x = 0;
		a.y = 0;

	}

}	

float vector2::Magnitude(vector2& a)
{
	return sqrt(a.x * a.x + a.y * a.y);
}

void vector2::Normalize(vector2& a)
{
	float mag = Magnitude(a);
	a.x /=mag; 
	a.y /=mag;
}