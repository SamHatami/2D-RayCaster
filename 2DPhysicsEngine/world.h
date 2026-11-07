#pragma once
#include "vector2.h"

namespace World
{
	//Units are in meters
	//Force in N
	//Mass in kg
	//Time in s
	//Velocity in m/s
	//Acceleration in m/s^2

	constexpr vector2 VERTICAL{0, 1};
	constexpr vector2 HORIZONTAL{1, 0};
	constexpr vector2 GRAVITY{0, 9.81f}; // m/s^2
	constexpr float GROUND_FRICTION = 0.8f;
	constexpr float AIR_DENSITY = 1.225f;
	constexpr float DRAG_COEFFICIENT = 0.47f;
};
