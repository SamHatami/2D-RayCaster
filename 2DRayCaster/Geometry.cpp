#include "Geometry.h"
#include <algorithm>


BoundingBox getBoundingBoxFromTriangle(Point& a, Point& b, Point& c)
{
	BoundingBox boundingBox = {
		std::min({a.x, b.x, c.x}),
		std::max({a.x, b.x, c.x}),
		std::min({a.y, b.y, c.y}),
		std::max({a.y, b.y, c.y}),
	};

	return boundingBox;
}

float distanceBetweenPoint(Point& a, Point& b)
{
	const float dx = a.x - b.x;
	const float dy = a.y - b.y;
	const float distance = sqrtf(dx * dx + dy * dy);

	return distance;
}

bool pointsAreCoincident(Point& a, Point& b)
{
	if (a.x == b.x && a.y == b.y)
		return true;
	return false;
}

Point getMidPoint(const Line& line)
{
	return Point{
		(line.start.x + line.end.x) * 0.5f,
		(line.start.y + line.end.y) * 0.5f
	};
}

Point getMidPoint(const Point& a, const Point& b)
{
	return Point{
		(a.x + b.x) * 0.5f,
		(a.y + b.y) * 0.5f
	};
}
