#pragma once
#include "Light.h"
class DirectionalLight :
    public Light
{
private:
	static constexpr float DEFAULT_RAY_LENGTH = 300.0f;
public:
    float raySpacing;
    float angularDirection;
	float rayLength;
	vector2 direction;

	DirectionalLight(float raySpacing = 0.0f, float angularDirection = 0.0f, float intensity = 100.0f, uint32_t color = 0xFFFFFF00);

	void castRays(const std::vector<Point> points = {}) override;
};

