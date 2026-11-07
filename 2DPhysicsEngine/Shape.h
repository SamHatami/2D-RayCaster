#pragma once
#include <cstdint>
#include "Vector2.h"

class Shape
{
public:
	virtual float GetInertia(float mass); //pure virtual GetInertia
	virtual vector2 GetCenterOfGravity(); //pure
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

class Circle : public Shape
{
public:
	vector2 center;
	float radius;
	uint32_t color;

	Circle(vector2 center, float radius, uint32_t color = 0xFFFFFF)
		: center(center), radius(radius), color(color)
	{
	}

	float GetInertia(float mass) override;
	vector2 GetCenterOfGravity() override;
};

class Rectangle : public Shape
{
public:
	vector2 start;
	int width;
	int height;
	uint32_t color;

	Rectangle(vector2 start, int width, int height, uint32_t color = 0xFFFFFF)
		: start(start), width(width), height(height), color(color)
	{
	}

	float GetInertia(float mass) override;
	vector2 GetCenterOfGravity() override;
};

struct BoundingBox
{
	float minX;
	float maxX;
	float minY;
	float maxY;
};
