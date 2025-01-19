#pragma once

class Polygon;

struct Edge
{
	size_t v1;
	size_t v2;
	bool isInternal;

	Polygon* parent;

	Edge(size_t v1, size_t v2, bool isInternal, Polygon* parent = nullptr);
};

