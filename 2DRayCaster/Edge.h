#pragma once
#include "Vector2.h"
#include "Geometry.h"
#include "Polygon.h"

class Polygon;

struct Edge
{
	size_t v1;
	size_t v2;
	bool isInternal;
	vector2 normal;

	Polygon* parent;

	Edge(size_t v1, size_t v2, bool isInternal, Polygon* parent = nullptr);
	Line toLine() const;
};

