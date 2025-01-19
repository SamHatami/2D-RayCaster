#include "LightingSystem.h"

#include <iostream>

#include "DirectionalLight.h"



void LightingSystem::updatePointLight(PointLight& light, const std::vector<Wall>& walls)
{
	light.castRays();

	// Loop through all rays
	for (int i = 0; i < light.getCurrentResolution(); i++)
	{
		// Initialize variables to track the closest hit for the current ray
		float closestHitDistance = light.getMaxRayLength();
		Point closestHitPoint;

		// Loop through all walls and check for intersections
		for (const auto& wall : walls)
		{
			// Check if the current ray hits the wall
			RayHitResult result = rayCaster.check_hit(light.rays[i], wall.definition, &light , true);

			// If a hit occurs and it's closer than the previous closest hit
			if (result.hasHit && result.distance < closestHitDistance)
			{
				closestHitDistance = result.distance;
				closestHitPoint = result.hitPoint;
			}
		}

		// Now closestHitPoint contains the closest hit point for ray[i]
		// You can update the ray hit result here if necessary:
		if (closestHitDistance < light.getRadius())
		{
			light.rays[i].hitResult = { true, closestHitPoint, closestHitDistance };
		}
		else
		{
			light.rays[i].hitResult = { false, {}, 0 };  // No hit
		}
	}
}

void LightingSystem::updateDirectionalLight(DirectionalLight& directional, const std::vector<Wall>& walls)
{
	std::vector<Point> endPoints;
	std::vector<Wall> culledWalls;

	for (int i = 4; i < walls.size(); i++) //add all endPoints, except boundary walls , then do check for distinct points.
	{
		float dot = vector2::Dot(walls[i].normal, directional.direction);
		if (dot < 0) //Shadowcasters
			continue;

		culledWalls.push_back(walls[i]);
		endPoints.push_back(walls[i].definition.start);
		endPoints.push_back(walls[i].definition.end);
	}

	std::cout << "DirectionalLight received " << endPoints.size() << " endpoints\n";

	directional.castRays(endPoints);

	for (auto& ray : directional.rays)
	{
		for (size_t i = 0; i < culledWalls.size(); i++)
		{
			RayHitResult hitResult = RayCaster::check_hit(ray, walls[i].definition);

			if (hitResult.hasHit && hitResult.distance < ray.length)
			{
				//ray.active = false;

			}
		}

	}
}
