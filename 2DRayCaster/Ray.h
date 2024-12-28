#pragma once
#include "Geometry.h"
#include "Vector2.h"

struct ray {
	point start;
	vector2 direction;
	uint32_t color;

	ray() : start{ 0, 0 }, direction{ 0, 0 }, color(0xFFFFFF) {}

	ray(const point& origin, const vector2& dir, const uint32_t col = 0)
	{
		start = origin;
		direction = dir.Normalized();
		color = col;
	}	

};

