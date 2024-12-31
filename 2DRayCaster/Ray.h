#pragma once
#include "Geometry.h"
#include "Vector2.h"

struct RayHitResult {
	bool hasHit;
	point hitPoint;
	float distance;
};

struct ray {
	point start;
	point end;
	float length;
	vector2 direction;
	uint32_t color;
	int rayNr;
	ray() : start{ 0, 0 }, direction{ 0, 0 }, color(0xFFFFFF), length{ 100 }{}

	ray(const point& origin, const vector2& dir, const float length, const uint32_t col = 0)
	{
		start = origin;
		direction = dir.Normalized();
		color = col;
		this->length = length;
		end.x = start.x + direction.x * length;
		end.y = start.y + direction.y * length;
	}	
};

