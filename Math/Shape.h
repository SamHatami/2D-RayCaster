#pragma once
#include "Geometry.h"

class Shape
{
public:
	constexpr static float point_inertia = 0.0f;

	virtual float GetInertia(float mass);

	virtual point GetCenterOfGravity();
};

class Circle : public Shape
{
public:
	float radius;
	point GetCenterOfGravity() override
	{
		return point(0, 0);
	}
	float GetInertia(float mass) override
	{
		return mass * radius * radius / 2;
	}
};

class Rectangle : public Shape
{
public:
	float width;
	float height;
	point GetCenterOfGravity() override
	{
		return point(width / 2, height / 2);
	}
	float GetInertia(float mass) override
	{
		return mass * (width * width + height * height) / 12;
	}
};

