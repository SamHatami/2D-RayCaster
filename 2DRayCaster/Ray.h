#pragma once
#include "Geometry.h"
#include "Vector2.h"

struct RayHitResult {
	bool hasHit;
	Point hitPoint;
	float distance;
};

struct Ray {
	Point start;
	Point end;
	float length;
	vector2 direction;
	uint32_t color;
	int rayNr;
	mutable RayHitResult hitResult;

	Ray();

	Ray(const Point& origin, const vector2& dir, const float maxLength, const uint32_t col);

	void resetHitResult();
};

