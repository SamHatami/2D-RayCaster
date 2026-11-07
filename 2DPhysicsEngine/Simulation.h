#pragma once
#include <vector>

#include "RigidBody.h"
#include "Trajectory.h"
#include "World.h"

class Simulation
{
public:
	float time = 0;
	float time_step = 0.02f;
	float time_duration = 3.0f;
	std::vector<RigidBody> rigid_bodies;

	void add_rigid_body(RigidBody rigid_body);
	void simulate();
};
