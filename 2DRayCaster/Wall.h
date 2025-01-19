#pragma once
#include "Geometry.h"
#include "Vector2.h"

struct Wall
{
	int height;
	Line definition;
	vector2 normal;

	Wall() : height(0), definition(Line()) {} // Default constructor

	Wall(int height, const Line& definition);

};

