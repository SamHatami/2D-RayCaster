#pragma once
#include "Geometry.h"
#include "Vector2.h"

struct RayHitResult {
	bool hasHit = false;
	Point hitPoint = {0,0};
	float distance = 0.0f;

};

struct Ray {
	Point start;
	Point end;
	float length;
	vector2 direction;
	uint32_t color;
	int rayNr;
	mutable RayHitResult hitResult;
	bool active = true;

	Ray();

	Ray(const Point& origin, const vector2& dir, const float maxLength, const uint32_t col);

	void resetHitResult();
};

