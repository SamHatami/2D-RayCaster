#pragma once
struct Point //Mathematically it make sense, not sure if this causes confusion, since it does the same as vec2. 
{
	float x;
	float y;

	Point(float x = 0, float y = 0) : x(x), y(y) {}

	friend Point operator+(const Point& a, const Point& b)
	{
		return Point(a.x + b.x, a.y + b.y);
	}

	friend Point operator-(const Point& a, const Point& b)
	{
		return Point(a.x - b.x, a.y - b.y);
	}

	friend Point operator*(const Point& a, float scalar)
	{
		return Point(a.x * scalar, a.y * scalar);
	}

	friend Point operator/(const Point& a, float scalar)
	{
		return Point(a.x / scalar, a.y / scalar);
	}


};

