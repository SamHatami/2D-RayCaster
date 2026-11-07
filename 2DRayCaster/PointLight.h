#pragma once
#include "Light.h"

class vector2Light :
	public Light
{
private:
	float radius;
	std::vector<vector2> boundaryvector2s;
	float maxRayLength = 200.0f;
	float angularRaySeperation;

public:

	void castRays(const std::vector<vector2> vector2s = {}) override;
	void updateBoundary();
	float getMaxRayLength();
	float getAngularDirection() const;
	float getRadius();
	std::vector<vector2> getBoundaryvector2s();

	vector2Light(float radius = 0.0f, float intensity = 100.0f,
		uint32_t color = 0xFFFFFF00, vector2 position = { 0,0 });
};
