#include "RayCaster.h"
#include <cmath>
#include "DirectionalLight.h"
#include "EDge.h"
#include "Light.h"
#include "PointLight.h"
#include "Vertex.h"

RayCaster::RayCaster()
{
}

//Probably obsolete, each light can cast their own rays.
void RayCaster::castRays(Light& lightSource)
{
	std::vector<Ray> rays = lightSource.getRays();

	switch (lightSource.getType())
	{
	case Light::LightType::Point:

		for (int i = 0; i < NR_OF_RAYS; i++)
		{
			point centerPoint = lightSource.getPosition();
			rays[i].resetHitResult();
			rays[i].start = centerPoint;
			rays[i].end = point{
				centerPoint.x + rays[i].direction.x * lightSource.MAX_RAY_LENGTH,
				centerPoint.y + rays[i].direction.y * lightSource.MAX_RAY_LENGTH
			};
		}
		break;

	case Light::LightType::Directional:

		DirectionalLight& dirLight = static_cast<DirectionalLight&>(lightSource);
		for (int i = 0; i < NR_OF_RAYS; i++)
		{
			point centerPoint = lightSource.getPosition();
			rays[i].resetHitResult();
			rays[i].start = point{
				i * dirLight.raySpacing * cosf(dirLight.angularDirection),
				i * dirLight.raySpacing * sinf(dirLight.angularDirection)
			};
			rays[i].end = point{
				rays[i].start.x + dirLight.direction.x * dirLight.rayLength,
				rays[i].start.y + dirLight.direction.y * dirLight.rayLength
			};
		}
		break;
	}
}

// each ray can do this instead...and why pointer to light Sam?
RayHitResult RayCaster::check_hit(const Ray& ray, const Light* light, const Edge& edge, const Polygon& polgyon, bool snapToEndPoints) 
{
	std::pair<const Vertex&, const Vertex&> vertices = polgyon.get_edge_vertices(edge);

	//Reset ray length

	//Line-Line Intersection from
	//https://www.topcoder.com/thrive/articles/Geometry%20Concepts%20part%202:%20%20Line%20Intersection%20and%20its%20Applications
	//https://www.geeksforgeeks.org/program-for-point-of-intersection-of-two-lines/
	//This is also referred in Real-Time Rendering 4th edition, p 1009

	//ray: a1x + b1y = c1
	const float a1 = ray.end.y - ray.start.y;
	const float b1 = ray.start.x - ray.end.x;
	const float c1 = a1 * ray.start.x + b1 * ray.start.y;

	//lineSegment: a2x + b2y = c2
	const float a2 = vertices.second.y - vertices.first.y;
	const float b2 = vertices.first.x - vertices.second.x;
	const float c2 = a2 * vertices.first.x + b2 * vertices.first.y;

	const float det = a1 * b2 - a2 * b1;
	if (abs(det) < EPSILON)
	{
		ray.hitResult = { false, {}, 0 };
		return ray.hitResult;
	}

	point hitPoint = {
		(b2 * c1 - b1 * c2) / det,
		(a1 * c2 - a2 * c1) / det,
	}; //Not const -> can be modified when trying to snap to endpoint

	//Since we are dealing with line segments we need to check if the hit point is on both lines
	if (!is_point_on_edge(hitPoint, vertices.first,vertices.second) || !is_point_on_line(hitPoint, { ray.start, ray.end }))
	{
		ray.hitResult = { false, {}, 0 };
		return ray.hitResult;
	}

	const float distanceToHit = sqrtf(powf(ray.start.x - hitPoint.x, 2) +
		powf(ray.start.y - hitPoint.y, 2));

	if (light != nullptr && snapToEndPoints)
	{
		float snapThreshold = 0.0f;

		if (const PointLight* pointLight = dynamic_cast<const PointLight*>(light)) {
			float raySpacing = distanceToHit * tanf(pointLight->getAngularDirection());
			snapThreshold = raySpacing * 0.6f;
		}

		try_snap_to_edge_vertices(hitPoint, vertices.first,vertices.second, snapThreshold);
	}

	const float distance =
		sqrtf(powf(ray.start.x - hitPoint.x, 2) + powf(ray.start.y - hitPoint.y, 2));

	//Beyond the ray, no hit
	if (distance > ray.length + EPSILON)
	{
		ray.hitResult = { false, {}, 0 };
		return ray.hitResult;
	}

	// If no previous hit or the current hit is closer, update hit result
	if (!ray.hitResult.hasHit || distance < ray.hitResult.distance)
	{
		ray.hitResult = { true, hitPoint, distance };
	}

	return ray.hitResult;
}

RayHitResult RayCaster::check_hit(const Ray& ray, const Line& lineSegment, const Light* light, bool snapToEndPoints) // each ray can do this instead
{
	//Reset ray length

	//Line-Line Intersection from
	//https://www.topcoder.com/thrive/articles/Geometry%20Concepts%20part%202:%20%20Line%20Intersection%20and%20its%20Applications
	//https://www.geeksforgeeks.org/program-for-point-of-intersection-of-two-lines/
	//This is also referred in Real-Time Rendering 4th edition, p 1009

	//ray: a1x + b1y = c1
	const float a1 = ray.end.y - ray.start.y;
	const float b1 = ray.start.x - ray.end.x;
	const float c1 = a1 * ray.start.x + b1 * ray.start.y;

	//lineSegment: a2x + b2y = c2
	const float a2 = lineSegment.end.y - lineSegment.start.y;
	const float b2 = lineSegment.start.x - lineSegment.end.x;
	const float c2 = a2 * lineSegment.start.x + b2 * lineSegment.start.y;

	const float det = a1 * b2 - a2 * b1;
	if (abs(det) < EPSILON)
	{
		ray.hitResult = { false, {}, 0 };
		return ray.hitResult;
	}

	point hitPoint = {
		(b2 * c1 - b1 * c2) / det,
		(a1 * c2 - a2 * c1) / det,
	}; //Not const -> can be modified when trying to snap to endpoint

	//Since we are dealing with line segments we need to check if the hit point is on both lines
	if (!is_point_on_line(hitPoint, lineSegment) || !is_point_on_line(hitPoint, { ray.start, ray.end }))
	{
		ray.hitResult = { false, {}, 0 };
		return ray.hitResult;
	}

	const float distanceToHit = sqrtf(powf(ray.start.x - hitPoint.x, 2) +
		powf(ray.start.y - hitPoint.y, 2));

	if (light != nullptr && snapToEndPoints)
	{
		float snapThreshold = 0.0f;

		if (const PointLight* pointLight = dynamic_cast<const PointLight*>(light)) {
			float raySpacing = distanceToHit * tanf(pointLight->getAngularDirection());
			snapThreshold = raySpacing * 0.6f;
		}

		try_snap_to_line_end_points(hitPoint, lineSegment, snapThreshold);
	}

	const float distance =
		sqrtf(powf(ray.start.x - hitPoint.x, 2) + powf(ray.start.y - hitPoint.y, 2));

	//Beyond the ray, no hit
	if (distance > ray.length + EPSILON)
	{
		ray.hitResult = { false, {}, 0 };
		return ray.hitResult;
	}

	// If no previous hit or the current hit is closer, update hit result
	if (!ray.hitResult.hasHit || distance < ray.hitResult.distance)
	{
		ray.hitResult = { true, hitPoint, distance };
	}

	return ray.hitResult;
}

//Only for lights don't already take endPoints in account
void RayCaster::try_snap_to_line_end_points(point& p, const Line& l, float snapThreshold)
{
	float dx = p.x - l.end.x;
	float dy = p.y - l.end.y;
	float distanceEnd = sqrtf(dx * dx + dy * dy);

	dx = p.x - l.start.x;
	dy = p.y - l.start.y;
	float distanceStart = sqrtf(dx * dx + dy * dy);

	if (distanceEnd < snapThreshold)
	{
		p = l.end;
	}
	else if (distanceStart < snapThreshold)
	{
		p = l.start;
	}
}

void RayCaster::try_snap_to_edge_vertices(point& p, const Vertex& v1, const Vertex& v2, float snapThreshold)
{
	float dx = p.x - v1.x;
	float dy = p.y - v1.y;
	float distance_to_v1 = sqrtf(dx * dx + dy * dy);

	dx = p.x - v2.x;
	dy = p.y - v2.y;
	float distance_to_v2 = sqrtf(dx * dx + dy * dy);

	if (distance_to_v1 < snapThreshold)
	{
		p = {v1.x,v1.y};
	}
	else if (distance_to_v2 < snapThreshold)
	{
		p = { v2.x,v2.y };
	}
}

//Claude helped me with this one. I had issues with some rays did not hit. Figured it was rounding errors due to fmin/fmax
//I'll have to read up on this
// https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html
bool RayCaster::is_point_on_line(const point& p, const Line& l)
{
	return p.x >= fmin(l.start.x, l.end.x) - RayCaster::EPSILON &&
		p.x <= fmax(l.start.x, l.end.x) + EPSILON &&
		p.y >= fmin(l.start.y, l.end.y) - EPSILON &&
		p.y <= fmax(l.start.y, l.end.y) + EPSILON;
}

bool RayCaster::is_point_on_edge(const point& p, const Vertex& v1, const Vertex& v2)
{

	return p.x >= fmin(v1.x, v2.x) - RayCaster::EPSILON &&
		p.x <= fmax(v1.x, v2.x) + EPSILON &&
		p.y >= fmin(v1.y, v2.y) - EPSILON &&
		p.y <= fmax(v1.y, v2.y) + EPSILON;
}