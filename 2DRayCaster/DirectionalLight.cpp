#include "DirectionalLight.h"



DirectionalLight::DirectionalLight(float raySpacing, float angularDirection, float intensity, uint32_t color)
	: Light(LightType::Directional, intensity, color, DEFAULT_RAY_LENGTH, Point{0, 0})
{
	this->angularDirection = angularDirection;
	this->raySpacing = raySpacing;

	direction = vector2{cos(angularDirection), sin(angularDirection)};
	rayLength = DEFAULT_RAY_LENGTH;
	rays.resize(static_cast<size_t>(globalResolution));
	for (int i = 0; i < rays.size(); i++)
	{
		rays[i].direction = direction;
		rays[i].direction.Normalize();
		rays[i].rayNr = i;
		rays[i].length = DEFAULT_RAY_LENGTH;
	}
}

void DirectionalLight::castRays(const std::vector<Point> points)
{
	//I could cast rays with a certain interval, but I just want to learn about shadows
	//raySpacing will be useless here, since I'll just create intermediate rays depending on the distance
	//between each point.

	//So the idea is:
	//Create rays towards each endpoint
	//Check for parallell and coincident rays, remove the one that has the farthest endPoint
	//Create intermediate points for future ray bouncing, should be an optional bool
	//Create secondary rays for pnumbra calculations, either here or by a seperate call from lightingsystem?
	if(points.empty())
		return;

	for(int i = 0; i < points.size(); i++)
	{
		
	}

	for (int i = 0; i < rays.size(); i++)
	{

		rays[i].resetHitResult();
		rays[i].start = Point{
			i * raySpacing * cosf(angularDirection),
			i * raySpacing * sinf(angularDirection)
		};
		rays[i].end = Point{
			rays[i].start.x + direction.x * rayLength,
			rays[i].start.y + direction.y * rayLength
		};
	}
}
