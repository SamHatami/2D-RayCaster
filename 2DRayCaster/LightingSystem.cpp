#include "LightingSystem.h"
#include "DirectionalLight.h"


void LightingSystem::updatePointLight(PointLight& light, const std::vector<Line>& walls)
{
	light.castRays();

	// Loop through all rays
	for (int i = 0; i < light.getCurrentResolution(); i++)
	{
		// Initialize variables to track the closest hit for the current ray
		float closestHitDistance = RayCaster::MAX_RAY_LENGTH;
		Point closestHitPoint;

		// Loop through all walls and check for intersections
		for (const auto& wall : walls)
		{
			// Check if the current ray hits the wall
			RayHitResult result = rayCaster.checkHit(light.rays[i], wall, light);

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

void LightingSystem::updateDirectionalLight(DirectionalLight& directional, const std::vector<Wall> walls)
{
	std::vector<Point> endPoints;

	for (int i = 0; walls.size(); i++) //add all endPoints, then do check for distinct points.
	{
		endPoints.push_back(walls[i].definition.start);
		endPoints.push_back(walls[i].definition.end);
	}

	directional.castRays(endPoints);
}
