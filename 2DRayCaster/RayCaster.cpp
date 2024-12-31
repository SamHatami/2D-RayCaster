#include "RayCaster.h"
#include <cmath>
#include <iostream>

RayCaster::RayCaster() //This is more or less basis for a round light
{


	for (int i = 0; i < NR_OF_RAYS; i++)
	{
		Rays[i].direction = vector2{ cos(i * piFactor), sin(i * piFactor) };
		Rays[i].direction.Normalize();
		Rays[i].rayNr = i;
	}
}

void RayCaster::CastRays(const point& startPoint)
{
	for (int i = 0; i < NR_OF_RAYS; i++)
	{
		Rays[i].start = startPoint;
		Rays[i].end = point{ startPoint.x + Rays[i].direction.x * Rays[i].length, startPoint.y + Rays[i].direction.y * Rays[i].length };
	}
}

RayHitResult RayCaster::CheckHit(const ray& ray, const line& testLine)
{
	//Reset ray length

	//Line-Line Intersection from
	//https://www.topcoder.com/thrive/articles/Geometry%20Concepts%20part%202:%20%20Line%20Intersection%20and%20its%20Applications
	//https://www.geeksforgeeks.org/program-for-point-of-intersection-of-two-lines/

	//ray: a1x + b1y = c1
	const float a1 = ray.end.y - ray.start.y;
	const float b1 = ray.start.x - ray.end.x;
	const float c1 = a1 * ray.start.x + b1 * ray.start.y;

	//testLine: a2x + b2y = c2
	const float a2 = testLine.end.y - testLine.start.y;
	const float b2 = testLine.start.x - testLine.end.x;
	const float c2 = a2 * testLine.start.x + b2 * testLine.start.y;

	const float det = a1 * b2 - a2 * b1;
	if (abs(det) < EPSILON) return { false, {}, 0.0f };

	if (det == 0) // Lines are parallel
	{
		return { false,{},0.0f };
	}

	const point hitPoint = {
		(b2 * c1 - b1 * c2) / det,
		(a1 * c2 - a2 * c1) / det,
	};

	//Since we are dealing with line segments we need to check if the hit point is on both lines
	if (!IsPointOnLine(hitPoint, testLine) || !IsPointOnLine(hitPoint, { ray.start, ray.end }))
		return { false, {}, 0.0f };

	const float distance =
		sqrtf(powf(ray.start.x - hitPoint.x, 2) + powf(ray.start.y - hitPoint.y, 2));

	if (distance > ray.length)
		return { false, {}, 0.0f };

	//Check the distance to the hit point and set length to it if smaller

	return { true, hitPoint, distance };
}

//Claude helped me with this one. I had issues with some rays did not hit. Figured it was rounding errors due to fmin/fmax
//I'll have to read up on this
// https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html
bool RayCaster::IsPointOnLine(const point& p, const line& l)
{
	return p.x >= fmin(l.start.x, l.end.x) - RayCaster::EPSILON &&
		p.x <= fmax(l.start.x, l.end.x) + EPSILON &&
		p.y >= fmin(l.start.y, l.end.y) - EPSILON &&
		p.y <= fmax(l.start.y, l.end.y) + EPSILON;
}