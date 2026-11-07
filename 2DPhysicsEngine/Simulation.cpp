#include "Simulation.h"

#include <iostream>
#include <ostream>

void Simulation::add_rigid_body(RigidBody rigid_body)
{
	rigid_bodies.push_back(rigid_body);
}

void Simulation::simulate()
{
	for (int i = 0; i < time_duration / time_step; i++)
	{
		for (auto& rigidBody : rigid_bodies)
		{
			time = time + time_step;

			rigidBody.apply_force({1000, 0}, time_step, true);

			std::cout << "Time: " << time << " - Position: (" << rigidBody.get_position().x << ", " << rigidBody.
				get_position().y << ")" << std::endl;
		}
	}
}