#include "RigidBody.h"

#include "world.h"

rigid_body::rigid_body(float mass, Shape shape, point start_position)
{
	this->mass_ = mass;
	this->shape_ = shape;
	inertia_ = shape.GetInertia(mass);
	torque_ = 0;
	angular_velocity_ = 0;
	center_of_gravity_ = shape.GetCenterOfGravity();
	position_ = start_position;
	velocity_ = vector2(0, 0);
	acceleration_ = vector2(0, 0);
}

rigid_body rigid_body::create_particle(float mass, point position)
{
	rigid_body particle = rigid_body(mass, Shape::CreatePoint(position));

	particle.position_ = position;
	particle.velocity_ = vector2(0, 0);
	particle.acceleration_ = vector2(0, 0);
	particle.inertia_ = Shape::point_inertia;
	particle.torque_ = 0;
	particle.angular_velocity_ = 0;
	particle.center_of_gravity_ = position;
	
	return particle;
}

void rigid_body::apply_force(vector2 force, float time_duration)
{
	velocity_ = velocity_ + (force / mass_) * time_duration - world::gravity;
}
