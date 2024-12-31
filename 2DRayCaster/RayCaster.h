#pragma once
#include "Ray.h"

class RayCaster
{
public:
	RayCaster();
	void CastRays(const point& startPoint);
	RayHitResult CheckHit(const ray& ray, const line& testLine);
	ray* GetRays() { return Rays; }
	int NrOfRays() { return NR_OF_RAYS; }

private:
	static constexpr float EPSILON = 0.0001f;
	static constexpr int NR_OF_RAYS = 64;
	static constexpr float piFactor = 2 * 3.14159265359f / NR_OF_RAYS;
	ray Rays[NR_OF_RAYS];
	point MouseStart;
	static bool IsPointOnLine(const point& p, const line& l);
};
