#pragma once
#include "DirectionalLight.h"
#include "PointLight.h"
#include "RayCaster.h"

class LightingSystem
{
public:
	LightingSystem() : rayCaster() {};
	void updatePointLight(PointLight& light, const std::vector<Line>& walls);
	void updateDirectionalLight(DirectionalLight& directional, const std::vector<Wall> wall);

private:
	RayCaster rayCaster;
};

