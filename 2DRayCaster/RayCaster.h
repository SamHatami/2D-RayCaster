#pragma once
#include "Light.h"
#include "Ray.h"
#include "Vertex.h"

class Light;

class RayCaster
{
public:
	RayCaster();
	void castRays(Light& lightSource);
	static RayHitResult check_hit(const Ray& ray, const Light* light, const Edge& edge, const Polygon& polgyon,
	                              bool snapToEndPoints);
	static RayHitResult check_hit(const Ray& ray, const Line& lineSegment, const Light* light = nullptr, bool snapToEndPoints = false);
	static constexpr float MAX_RAY_LENGTH = 200;
	static constexpr int NR_OF_RAYS = 128;


private:
	static constexpr float EPSILON = 0.0001f;
		point mouseStart;
	static bool is_point_on_line(const point& p, const Line& l);
	static bool is_point_on_edge(const point& p, const Vertex& v1, const Vertex& v2);
	static void try_snap_to_line_end_points(point& p, const Line& l, float snapThreshold);
	static void try_snap_to_edge_vertices(point& p, const Vertex& v1, const Vertex& v2, float snapThreshold);
};
