#include "DirectionalLight.h"

#include "Display.h"
#include "RayCaster.h"

DirectionalLight::DirectionalLight(float raySpacing, float angularDirection, float intensity, uint32_t color)
	: Light(LightType::Directional, intensity, color, DEFAULT_RAY_LENGTH, vector2{ 0, 0 })
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

void DirectionalLight::castRays(const std::vector<vector2> endvector2s)
{
	//Perhaps I should check what is in shadow instead of what is lit?

	//I could cast rays with a certain interval, but that would require alot of rays to be sure that all the endvector2s are hit.
	//raySpacing will be useless here, since I'll just create intermediate rays depending on the distance between each vector2.

	//So the idea is:
	//Create rays towards each endvector2
	//Check for rays that merge, remove the one that has the farthest endvector2 <--- Not sure if this should happen here.
	//Create intermediate endvector2s for future ray bouncing, should be an optional bool and happen in later stage.
	//Create secondary rays for pnumbra calculations, either here or by a seperate call from lightingsystem?

	if (endvector2s.empty())
		return;

	initalizeRays(endvector2s.size()); // probably not a good idea to resize this all the time, but should be called if somthing changes in the window.
	std::vector<Line> boundaries = Display::getWindowBorders();

	for (int i = 0; i < endvector2s.size(); i++)
	{
		rays[i].resetHitResult();

		float startX = endvector2s[i].x + direction.x * rayLength;
		float startY = endvector2s[i].y + direction.y * rayLength;

		rays[i].start = endvector2s[i];
		rays[i].end = vector2{ startX, startY };
		rays[i].length = rayLength;

		//Check against window boundary to get the endvector2 and change the length of the ray
		//TODO The length of the ray should automatically be recalculated evertime start or end vector2 are changed

		for (int j = 0; j < boundaries.size(); j++)
		{
			RayHitResult hit_result = RayCaster::check_hit(rays[i], boundaries[j]);

			if (hit_result.hasHit)
			{
				rays[i].end = hit_result.hitvector2;
				rays[i].length = distanceBetweenvector2(rays[i].start, rays[i].end);
				break;
			}
		}
	}




}

bool DirectionalLight::isActive() const
{
	return active;
}

//Kept for notes: If the scene was to be flooded with rays to:
//for (int i = 0; i < rays.size(); i++)
//{
//
//	rays[i].start = vector2{
//		i * raySpacing * cosf(angularDirection),
//		i * raySpacing * sinf(angularDirection)
//	};
//	rays[i].end = vector2{
//		rays[i].start.x + direction.x * rayLength,
//		rays[i].start.y + direction.y * rayLength
//	};
//}