#pragma once
#include "Vector2.h"
#include "Geometry.h"

struct Vertex;;
class Polygon;

struct Edge
{
	Vertex& v1;
	Vertex& v2;
	bool isInternal;
	vector2 normal;

	Polygon* parent;

	Edge(Vertex& v1, Vertex& v2, bool isInternal);
	Line toLine() const;
	Edge& operator=(const Edge& other);
};

