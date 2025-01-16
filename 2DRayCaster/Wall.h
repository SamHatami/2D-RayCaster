#pragma once
#include "Geometry.h"

struct Wall
{
	int height;
	Line definition;

	Wall() : height(0), definition(Line()) {} // Default constructor

	Wall(int height, const Line& definition) : height(height), definition(definition) {  }

};

