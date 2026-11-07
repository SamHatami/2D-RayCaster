#include "Geometry.h"
#include <algorithm>


BoundingBox getBoundingBoxFromTriangle(vector2& a, vector2& b, vector2& c)
{
	BoundingBox boundingBox = {
		std::min({a.x, b.x, c.x}),
		std::max({a.x, b.x, c.x}),
		std::min({a.y, b.y, c.y}),
		std::max({a.y, b.y, c.y}),
	};

	return boundingBox;
}

float distanceBetweenvector2(vector2& a, vector2& b)
{
	const float dx = a.x - b.x;
	const float dy = a.y - b.y;
	const float distance = sqrtf(dx * dx + dy * dy);

	return distance;
}

bool vector2sAreCoincident(vector2& a, vector2& b)
{
	if (a.x == b.x && a.y == b.y)
		return true;
	return false;
}

vector2 getMidvector2(const Line& line)
{
	return vector2{
		(line.start.x + line.end.x) * 0.5f,
		(line.start.y + line.end.y) * 0.5f
	};
}

vector2 getMidvector2(const vector2& a, const vector2& b)
{
	return vector2{
		(a.x + b.x) * 0.5f,
		(a.y + b.y) * 0.5f
	};
}
