#pragma once
#include "Geometry.h"
#include "Polygon.h"


struct Vertex
{
	float x;
	float y;
	uint32_t color;
	Polygon* parent;
	size_t internalNr; //
	size_t globalNr; //This should be known by a "scene-manager" that which the vertex class can ask for next available globalNr.

	Vertex(float x = 0, float y = 0, uint32_t color = 0xFFFFFFFF, Polygon* parent = nullptr);
	Point toPoint() const;
};


