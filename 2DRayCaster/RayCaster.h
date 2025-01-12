#pragma once
#include "Light.h"
#include "Ray.h"

class Light;

class RayCaster
{
public:
	RayCaster();
	void castRays(Light& lightSource);
	RayHitResult checkHit(const Ray& ray, const Line& lineSegment, Light& light);
	static constexpr float MAX_RAY_LENGTH = 200;
	static constexpr int NR_OF_RAYS = 128;


private:
	static constexpr float EPSILON = 0.0001f;
		Point mouseStart;
	static bool isPointOnLine(const Point& p, const Line& l);
	void trySnapToVertex(Point& p, const Line& l, float snapThreshold);
};
