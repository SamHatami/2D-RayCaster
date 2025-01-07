#include "Light.h"
#include "Ray.h"
#include "RayCaster.h"

Light::Light()
	: radius(100)
	  , intensity(100)
	  , color(0xFFFFFF00)
	  , lightType(LightType::Point)
	  , lightBehaviour(LightBehaviour::Static)
	  , rayCaster(std::make_unique<RayCaster>())
{
}

Light::Light(int radius, float intensity, uint32_t color, LightType type, RayCaster* rayCaster)
	: radius(radius)
	  , intensity(intensity)
	  , color(color)
	  , lightType(type)
	  , lightBehaviour(LightBehaviour::Static)
	  , rayCaster(rayCaster)
{
	boundaryPoints.resize(rayCaster->nrOfRays());
	rays = rayCaster->getRays();

	updateBoundary();
}

void Light::setPosition(const Point& pos)
{
	centerPoint = pos;
}

void Light::setColor(const uint32_t newColor)
{
	color = newColor;
}

std::vector<Point> Light::getBoundaryPoints()
{
	return boundaryPoints;
}

Point& Light::getCenterPoint()
{
	return centerPoint;

}



Light::LightType Light::type() const
{
	return lightType;
}


void Light::updateBoundary()
{
	rays = rayCaster->getRays();
	int rayCount = rayCaster->nrOfRays();

	for (int i = 0; i < rayCount; i++)
	{
		if (rays[i].hitResult.hasHit)
		{
			boundaryPoints[i] = rays[i].hitResult.hitPoint;
		}
		else
		{
			boundaryPoints[i] = rays[i].end;
		}
	}
}

//Light::LightType Light::type() const
//{
//	return lightType;
//
//}

void Light::decreaseIntensity()
{
	if (intensity != 0)
		intensity -= 10;
}

void Light::increaseIntensity()
{
	intensity += 10;
}

float Light::getIntensity() const
{
	return intensity;
}

uint32_t Light::getColor() const
{
	return color;
}
