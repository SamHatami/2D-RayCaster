#pragma once
#include <cstdint>
#include "Vector2.h"

struct world
{
	constexpr static vector2 vertical= { 0,1 };
	constexpr static vector2 horizontal = { 1,0 };
	constexpr static vector2 gravity = {0,9.81f};
	constexpr static float ground_friction = 0.8f;
	constexpr static float air_density = 1.225f;
	constexpr static float drag_coefficient = 0.47f;
};



