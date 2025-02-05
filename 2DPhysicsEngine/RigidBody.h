#pragma once
#include "Shape.h"
#include "Vector2.h"

struct point;

class rigid_body
{
private:
	float mass_;
	vector2 velocity_;
	vector2 acceleration_;
	float inertia_;
	float torque_;
	float angular_velocity_;
	point center_of_gravity_;
	point position_;
	Shape shape_;
public:

	rigid_body(float mass, Shape shape, point start_position);
	static rigid_body create_particle(float mass, point position);
	void apply_force(vector2 force, float time_duration);
};
