#include "RayCaster.h"




void RayCaster::CastRays(point& mousePoint)
{
	for (int i = 0; i < 10; i++)
	{
		rays_[i].start = mousePoint;
		rays_[i].direction = vector2{ (float)cos(i * 0.1f), (float)sin(i * 0.1f) };
	}
}



void RayCaster::CheckIntersection(ray&, line&)
{
}


