#include "PointLight.h"

PointLight::PointLight(float radius, float intensity, uint32_t color, Point position)
    : Light(LightType::Point, intensity, color, maxRayLength, position)
{
    this->radius = radius;
    angularRaySeperation = 2 * 3.14159265359f / static_cast<int>(globalResolution);

    if (radius == 0.0f) {
        this->radius = MAX_RAY_LENGTH;
        maxRayLength = MAX_RAY_LENGTH;
    }
    else {
        maxRayLength = this->radius;
    }

    // Initialize rays
    rays.resize(static_cast<size_t>(globalResolution));
    for (int i = 0; i < rays.size(); i++)
    {
        rays[i].direction = vector2{ static_cast<float>(cos(i * angularRaySeperation)), static_cast<float>(sin(i * angularRaySeperation)) };
        rays[i].direction.Normalize();
        rays[i].rayNr = i;
        rays[i].length = radius;
    }

    // Initialize boundary points with proper positions
    boundaryPoints.resize(rays.size());

    castRays();
    updateBoundary();
}

void PointLight::castRays(const std::vector<Point> points)
{
    for (int i = 0; i < rays.size(); i++)
    {
        
        rays[i].resetHitResult();
        rays[i].start = position;
        rays[i].end = Point{
            position.x + rays[i].direction.x * maxRayLength,
            position.y + rays[i].direction.y * maxRayLength
        };
    }
}

void PointLight::updateBoundary()
{
    for (size_t i = 0; i < rays.size(); i++)
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

float PointLight::getMaxRayLength()
{
    return maxRayLength;
}

float PointLight::getAngularDirection() const
{
    return  angularRaySeperation;
}

float PointLight::getRadius()
{
    return radius;
}

std::vector<Point> PointLight::getBoundaryPoints()
{
	return boundaryPoints;
}

