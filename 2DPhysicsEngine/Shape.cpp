#include "Shape.h"

#include "Vector2.h"

float Circle::GetInertia(float mass)
{
	return mass * radius * radius / 2;
}

vector2 Circle::GetCenterOfGravity()
{
	return center;
}

float Rectangle::GetInertia(float mass)
{
	return mass * (width * width + height * height) / 12;
}

vector2 Rectangle::GetCenterOfGravity()
{
	return {start.x + width / 2, start.y + height / 2};
}

float ::Shape::GetInertia(float mass)
{
	return 0.0f;
}

vector2 Shape::GetCenterOfGravity()
{
	return vector2();
}