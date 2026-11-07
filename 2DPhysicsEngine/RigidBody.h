#pragma once

#include <memory>
#include <vector>

#include "Shape.h"
#include "Vector2.h"

class RigidBody
{
private:
	float mass_;
	vector2 velocity_;
	vector2 acceleration_;
	float inertia_;
	float torque_;
	float angular_velocity_;
	vector2 center_of_gravity_;
	vector2 position_;
	std::vector<vector2> trajectory;
	std::shared_ptr<Shape> shape_;

public:
	RigidBody(float mass, std::shared_ptr<Shape> shape, vector2 start_position);
	static RigidBody create_particle(float mass, vector2 position);
	void apply_force(vector2 force, float time_duration, bool gravity);
	vector2 get_position() const { return position_; }
	std::vector<vector2> get_trajectory();
};
