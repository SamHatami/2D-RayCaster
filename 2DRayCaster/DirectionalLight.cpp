#include "DirectionalLight.h"

#include "Display.h"
#include "RayCaster.h"

DirectionalLight::DirectionalLight(float raySpacing, float angularDirection, float intensity, uint32_t color)
	: Light(LightType::Directional, intensity, color, DEFAULT_RAY_LENGTH, Point{ 0, 0 })
{
	this->angularDirection = angularDirection;
	this->raySpacing = raySpacing;

	direction = vector2{ cos(angularDirection), sin(angularDirection) };
	rayLength = DEFAULT_RAY_LENGTH;

	std::pair<int, int>  winDimensions = Display::getWindowDimensions();

	widthBoundary = std::get<0>(winDimensions);
	heightBoundary = std::get<1>(winDimensions);
}

void DirectionalLight::initalizeRays(int nrOfRays)
{
	rays.resize(static_cast<size_t>(nrOfRays));
	for (int i = 0; i < rays.size(); i++)
	{
		rays[i].direction = direction;
		rays[i].direction.Normalize();
		rays[i].rayNr = i;
		rays[i].length = DEFAULT_RAY_LENGTH;
	}
}

void DirectionalLight::castRays(const std::vector<Point> endPoints)
{
	//I could cast rays with a certain interval, but that would require alot of rays to be sure that all the endpoints are hit.
	//raySpacing will be useless here, since I'll just create intermediate rays depending on the distance between each point.

	//So the idea is:
	//Create rays towards each endpoint
	//Check for rays that merge, remove the one that has the farthest endPoint <--- Not sure if this should happen here.
	//Create intermediate endPoints for future ray bouncing, should be an optional bool and happen in later stage.
	//Create secondary rays for pnumbra calculations, either here or by a seperate call from lightingsystem?

	if (endPoints.empty())
		return;

	initalizeRays(endPoints.size()); // probably not a good idea to resize this all the time, but should be called if somthing changes in the window.

	for (int i = 0; i < endPoints.size(); i++)
	{
		rays[i].resetHitResult();
		rays[i].end = endPoints[i];
		rays[i].start = Point{
			endPoints[i].x + direction.x * rayLength, // this should hit the window boundary
			endPoints[i].y + direction.y * rayLength// this should hit the window boundary
		};
	}

	//Check against window boundary to get the endpoint

	const std::vector<Line> boundaries = Display::getWindowBorders();

	for (int i = 0; i < rays.size(); i++)
	{
		for (int j = 0; j < boundaries.size(); j++)
		{
			RayHitResult hit_result = RayCaster::check_hit(rays[j], boundaries[j]);

			if (hit_result.hasHit)
			{
				rays[i].end = hit_result.hitPoint;
				break;
			}
		}
	}
}

//Kept for notes: If the scene was to be flooded with rays to:
//for (int i = 0; i < rays.size(); i++)
//{
//
//	rays[i].start = Point{
//		i * raySpacing * cosf(angularDirection),
//		i * raySpacing * sinf(angularDirection)
//	};
//	rays[i].end = Point{
//		rays[i].start.x + direction.x * rayLength,
//		rays[i].start.y + direction.y * rayLength
//	};
//}