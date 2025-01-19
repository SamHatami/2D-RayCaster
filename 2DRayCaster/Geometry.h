#pragma once
#include <SDL.h>

//Non light interactive

struct Point //Mathematically it make sense, not sure if this causes confusion, since it does the same as vec2. 
{
	float x;
	float y;

	Point(float x = 0, float y = 0) : x(x), y(y){}


};

struct Line
{
	Point start;
	Point end;
	uint32_t color;

	Line() : start(Point()), end(Point()), color(0)
	{
	}

	Line(Point start, Point end, uint32_t color = 0xFFFFFF)
		: start(start), end(end), color(color)
	{
	}

};

struct Circle
{
	Point center;
	float radius;
	uint32_t color;

	Circle(Point center, float radius, uint32_t color = 0xFFFFFF)
		: center(center), radius(radius), color(color)
	{
	}
};

struct Rectangle
{
	Point start;
	int width;
	int height;
	uint32_t color;

	Rectangle(Point start, int width, int height, uint32_t color = 0xFFFFFF)
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

BoundingBox getBoundingBoxFromTriangle(Point& a, Point& b, Point& c);
float distanceBetweenPoint(Point& a, Point& b);
bool pointsAreCoincident(Point& a, Point& b);
Point getMidPoint(const Line& line);

Point getMidPoint(const Point& a, const Point& b);
