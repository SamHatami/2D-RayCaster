#pragma once
#include <cstdint>

//Non light interactive

struct point //Mathematically it make sense, not sure if this causes confusion, since it does the same as vec2. 
{
	float x;
	float y;

	point(float x = 0, float y = 0) : x(x), y(y){}


};

struct Line
{
	point start;
	point end;
	uint32_t color;

	Line() : start(point()), end(point()), color(0)
	{
	}

	Line(point start, point end, uint32_t color = 0xFFFFFF)
		: start(start), end(end), color(color)
	{
	}

};

struct Circle
{
	point center;
	float radius;
	uint32_t color;

	Circle(point center, float radius, uint32_t color = 0xFFFFFF)
		: center(center), radius(radius), color(color)
	{
	}
};

struct Rectangle
{
	point start;
	int width;
	int height;
	uint32_t color;

	Rectangle(point start, int width, int height, uint32_t color = 0xFFFFFF)
		: start(start), width(width), height(height), color(color)
	{
	}
};

struct BoundingBox
{
	float minX;
	float maxX;
	float minY;
	float maxY;
};

BoundingBox getBoundingBoxFromTriangle(point& a, point& b, point& c);
float distanceBetweenPoint(point& a, point& b);
bool pointsAreCoincident(point& a, point& b);
point getMidPoint(const Line& line);

point getMidPoint(const point& a, const point& b);
