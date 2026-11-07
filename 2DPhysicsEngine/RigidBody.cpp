#include "RigidBody.h"
#include "World.h"
#include "vector2.h"

RigidBody::RigidBody(float mass, std::shared_ptr<Shape> shape, vector2 start_position)
	: mass_(mass), position_(start_position), shape_(std::move(shape))
{
	inertia_ = shape_->GetInertia(mass);
	torque_ = 0;
	angular_velocity_ = 0;
	center_of_gravity_ = shape_->GetCenterOfGravity();
	velocity_ = vector2(0, 0);
	acceleration_ = vector2(0, 0);
}

RigidBody RigidBody::create_particle(float mass, vector2 position)
{
	auto particleShape = std::make_shared<Circle>(position, 2.0f);
	auto particle = RigidBody(mass, std::move(particleShape), position);

	particle.position_ = position;
	particle.velocity_ = vector2(0, 0);
	particle.acceleration_ = vector2(0, 0);
	particle.inertia_ = 1.0f;
	particle.torque_ = 0;
	particle.angular_velocity_ = 0;
	particle.center_of_gravity_ = position;

	return particle;
}

void RigidBody::apply_force(vector2 force, float time_duration, bool gravity)
{
	velocity_ = velocity_ + (force / mass_) * time_duration;

	if (gravity)
		velocity_ = velocity_ - World::GRAVITY;

	position_ = position_ + velocity_ * time_duration;

	trajectory.push_back(position_);
}

std::vector<vector2> RigidBody::get_trajectory()
{
	return trajectory;
}
