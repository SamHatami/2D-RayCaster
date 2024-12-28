#pragma once
#include "Ray.h"

class RayCaster
{
public:
	void CastRays(point& point);
	void CheckIntersection(ray&, line&);
	ray* GetRays() { return rays_; }

private:
	ray rays_[10];
	point mouse_start_;

};






