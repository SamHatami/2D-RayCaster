#include "Light.h"


Light::Resolution Light::globalResolution = Light::Resolution::Medium;

void Light::setColor(const uint32_t newColor)
{
	color = newColor;
}

point& Light::getPosition()
{
	return position;
}

void Light::setPosition(const point& pos)
{
	position = pos;
}

std::vector<Ray>& Light::getRays()
{
	return rays;
}

int Light::getCurrentResolution()
{
	
	return static_cast<int>(globalResolution);
	
}


Light::LightType Light::getType() const
{
	return lightType;
}


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

void Light::castRays(const std::vector<point> points)
{

}

uint32_t Light::getColor() const
{
	return color;
}
