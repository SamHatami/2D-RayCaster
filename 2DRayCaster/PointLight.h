#pragma once
#include "Light.h"

class PointLight :
	public Light
{
private:
	float radius;
	std::vector<Point> boundaryPoints;
	float maxRayLength = 200.0f;
	float angularRaySeperation;

public:

	void castRays(const std::vector<Point> points = {}) override;
	void updateBoundary();
	float getAngularDirection() const;
	float getRadius();
	std::vector<Point> getBoundaryPoints();

	PointLight(float radius = 0.0f, float intensity = 100.0f,
		uint32_t color = 0xFFFFFF00, Point position = { 0,0 });
};
