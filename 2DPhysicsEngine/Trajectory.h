#pragma once
#include <vector>

#include "RigidBody.h"

struct Trajectory
{
	const RigidBody& rigid_body;
	std::vector<vector2> positions;
};
