#pragma once
#include <cstdint>

//Non light interactive

struct vector2 //Mathematically it make sense, not sure if this causes confusion, since it does the same as vec2. 
{
	float x;
	float y;

	vector2(float x = 0, float y = 0) : x(x), y(y){}


};

struct Line
{
	vector2 start;
	vector2 end;
	uint32_t color;

	Line() : start(vector2()), end(vector2()), color(0)
	{
	}

	Line(vector2 start, vector2 end, uint32_t color = 0xFFFFFF)
		: start(start), end(end), color(color)
	{
	}

};

struct Circle
{
	vector2 center;
	float radius;
	uint32_t color;

	Circle(vector2 center, float radius, uint32_t color = 0xFFFFFF)
		: center(center), radius(radius), color(color)
	{
	}
};

struct Rectangle
{
	vector2 start;
	int width;
	int height;
	uint32_t color;

	Rectangle(vector2 start, int width, int height, uint32_t color = 0xFFFFFF)
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

BoundingBox getBoundingBoxFromTriangle(vector2& a, vector2& b, vector2& c);
float distanceBetweenvector2(vector2& a, vector2& b);
bool vector2sAreCoincident(vector2& a, vector2& b);
vector2 getMidvector2(const Line& line);

vector2 getMidvector2(const vector2& a, const vector2& b);
