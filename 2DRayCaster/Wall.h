#pragma once
#include "Geometry.h"

struct Wall
{
	int height;
	Line definition;

	Wall(int height, const Line& definition) : height(height), definition(definition) {  }

};

