#pragma once
#include "DirectionalLight.h"
#include "Display.h"
#include "vector2Light.h"
#include "Polygon.h"
#include "RayCaster.h"

class LightingSystem
{
public:
	LightingSystem() : rayCaster() {};
	void updatevector2Light(vector2Light& light, const std::vector<Polygon>& polgyons);
	void updateDirectionalLight(DirectionalLight& directional, const std::vector<Wall>& wall);
	void updateDirectionalLight(DirectionalLight& directional, const std::vector<Polygon>& polygons);
	void drawDirectionaLight(DirectionalLight& directional, Display& display);

private:
	RayCaster rayCaster;
	Shadow createShadow(DirectionalLight& directional, const std::vector<Edge>& edges);
};

