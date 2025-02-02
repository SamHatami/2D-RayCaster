#pragma once
#include "DirectionalLight.h"
#include "Display.h"
#include "PointLight.h"
#include "Polygon.h"
#include "RayCaster.h"

class LightingSystem
{
public:
	LightingSystem() : rayCaster() {};
	void updatePointLight(PointLight& light, const std::vector<Polygon>& polgyons);
	void updateDirectionalLight(DirectionalLight& directional, const std::vector<Wall>& wall);
	void updateDirectionalLight(DirectionalLight& directional, std::vector<Polygon>& polygons);
	void drawDirectionaLight(DirectionalLight& directional, Display& display);

private:
	RayCaster rayCaster;
	Shadow createShadow(DirectionalLight& directional, const std::vector<Edge>& edges);
};

