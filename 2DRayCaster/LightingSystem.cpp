#include "LightingSystem.h"

#include <iostream>

#include "DirectionalLight.h"
#include "Display.h"
#include "Polygon.h"


void LightingSystem::updatePointLight(PointLight& light, const std::vector<Polygon>& polgyons)
{
	light.castRays();

	// Loop through all rays
	for (int i = 0; i < light.getCurrentResolution(); i++)
	{
		// Initialize variables to track the closest hit for the current ray
		float closestHitDistance = light.getMaxRayLength();
		Point closestHitPoint;

		// Loop through all walls and check for intersections
		for (const auto& polygon : polgyons)
		{
			const std::vector<Edge>& polygonEdges = polygon.get_all_edges();
			//if any of the edge are facing away from the light source, ignore checking hit

			for (const auto& edge : polygonEdges)
			{
				RayHitResult result = rayCaster.check_hit(light.rays[i],&light, edge, polygon,true);

				// If a hit occurs and it's closer than the previous closest hit
				if (result.hasHit && result.distance < closestHitDistance)
				{
					closestHitDistance = result.distance;
					closestHitPoint = result.hitPoint;
				}
			}

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
}

[[deprecated]]
void LightingSystem::updateDirectionalLight(DirectionalLight& directional, const std::vector<Wall>& walls)
{
	std::vector<Point> endPoints;
	std::vector<Wall> culledWalls;

	for (int i = 0; i < walls.size(); i++) //add all endPoints, except boundary walls , then do check for distinct points.
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

void LightingSystem::updateDirectionalLight(DirectionalLight& directional, std::vector<Polygon>& polygons)
{
	for (auto& polygon : polygons)
	{
		// Simple shadow test - if any edge faces away from light, create shadow
		bool needsShadow = false;
		for (const auto& edge : polygon.get_all_edges())
		{
			float dot = vector2::Dot(edge.normal, directional.direction);
			if (dot > 0)
			{
				needsShadow = true;
				break;
			}
		}

		if (needsShadow)
		{
			Shadow shadow = createShadow(directional, polygon.get_all_edges());
			polygon.set_shadow(shadow);
		}
	}
}

Shadow LightingSystem::createShadow(DirectionalLight& directional, const std::vector<Edge>& edges)
{
	std::vector<Point> shadowPoints;

	// Get vertices from shadow-casting edges
	for (const auto& edge : edges)
	{
		float dot = vector2::Dot(edge.normal, directional.direction);
		if (dot > 0)
		{
			// Add original points
			shadowPoints.push_back(edge.v1.toPoint());
			shadowPoints.push_back(edge.v2.toPoint());

			// Add projected points
			float projectionLength = 1000.0f; // Just make it long enough to cover screen
			shadowPoints.push_back({
				edge.v1.x + directional.direction.x * projectionLength,
				edge.v1.y + directional.direction.y * projectionLength
				});
			shadowPoints.push_back({
				edge.v2.x + directional.direction.x * projectionLength,
				edge.v2.y + directional.direction.y * projectionLength
				});
		}
	}

	Shadow shadow;
	shadow.boundary_points = shadowPoints;
	return shadow;
}

