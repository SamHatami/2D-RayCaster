#pragma once
#include "Light.h"
class DirectionalLight :
    public Light
{
private:
	static constexpr float DEFAULT_RAY_LENGTH = 8000.0f;
	int heightBoundary;
	int widthBoundary;
	bool active = true;
	void initalizeRays(int nrOfRays);
public:
    float raySpacing;
    float angularDirection;
	float rayLength;
	vector2 direction;

	DirectionalLight(float raySpacing = 0.0f, float angularDirection = 0.0f, float intensity = 100.0f, uint32_t color = 0xFFFFFF00);

	void castRays(const std::vector<point> endPoints = {}) override;

	bool isActive() const;

};

