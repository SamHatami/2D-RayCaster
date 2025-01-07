#pragma once
#include <memory>
#include <vector>
#include "Ray.h"
#include "Geometry.h"
#include "RayCaster.h"

class RayCaster;

class Light
{
public:
	enum class LightType
	{
		Point,
		Spot,
		Directional
	};

	enum class LightBehaviour
	{
		Static,
		Dynamic
	};

private:
	int radius; //Does nothing for now 
	float intensity;
	std::vector<Point> boundaryPoints;
	uint32_t color;
	LightType lightType;
	LightBehaviour lightBehaviour;
	Point centerPoint;
	std::unique_ptr<RayCaster> rayCaster;
	Ray* rays;

public:
	Light();
	Light(int radius, float intensity, uint32_t color, LightType type, RayCaster* rayCaster);
	void setPosition(const Point& pos);
	void setColor(uint32_t newColor);
	float getIntensity() const;
	uint32_t getColor() const;
	std::vector<Point> getBoundaryPoints();
	Point& getCenterPoint();
	LightType type() const;
	void updateBoundary();
	void decreaseIntensity();
	void increaseIntensity();
};
