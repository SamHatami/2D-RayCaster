#pragma once
#include "PointLight.h"
#include "RayCaster.h"

class LightingSystem
{
public:
	LightingSystem() : rayCaster() {};
	void updatePointLight(PointLight& light, const std::vector<Line>& walls);

private:
	RayCaster rayCaster;
};

