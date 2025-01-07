#include "Ray.h"

#include <cfloat>

#include "RayCaster.h"

Ray::Ray() : start{ 0, 0 }, direction{ 0, 0 }, color(0xFFFFFF), rayNr(0), length{ RayCaster::MAX_RAY_LENGTH }
{
	//is this needed?
}

Ray::Ray(const Point& origin, const vector2& dir, const float maxLength, const uint32_t col = 0)
{
	start = origin;
	direction = dir.Normalized();
	color = col;
	length = maxLength;
	end.x = start.x + direction.x * maxLength;
	end.y = start.y + direction.y * maxLength;

	hitResult.hasHit = false;
	hitResult.hitPoint = Point();
	hitResult.distance = maxLength;
}

void Ray::resetHitResult()
{
	hitResult.hasHit = false;
	hitResult.hitPoint = Point();
	hitResult.distance = length;
}
