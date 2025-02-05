#include "Geometry.h"
#include <algorithm>


BoundingBox getBoundingBoxFromTriangle(point& a, point& b, point& c)
{
	BoundingBox boundingBox = {
		std::min({a.x, b.x, c.x}),
		std::max({a.x, b.x, c.x}),
		std::min({a.y, b.y, c.y}),
		std::max({a.y, b.y, c.y}),
	};

	return boundingBox;
}

float distanceBetweenPoint(point& a, point& b)
{
	const float dx = a.x - b.x;
	const float dy = a.y - b.y;
	const float distance = sqrtf(dx * dx + dy * dy);

	return distance;
}

bool pointsAreCoincident(point& a, point& b)
{
	if (a.x == b.x && a.y == b.y)
		return true;
	return false;
}

point getMidPoint(const Line& line)
{
	return point{
		(line.start.x + line.end.x) * 0.5f,
		(line.start.y + line.end.y) * 0.5f
	};
}

point getMidPoint(const point& a, const point& b)
{
	return point{
		(a.x + b.x) * 0.5f,
		(a.y + b.y) * 0.5f
	};
}
