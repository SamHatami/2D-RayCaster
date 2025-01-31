#include "Edge.h"

Edge::Edge(size_t v1, size_t v2, bool isInternal, Polygon* parent)
    : v1(v1)
    , v2(v2)
    , isInternal(isInternal)
    , parent(parent)
{
	vector2 tempVector = vector2::PointsToVector2(parent->get_vertex_at_index(v1).toPoint(), parent->get_vertex_at_index(v2).toPoint());
	tempVector.Normalize();
	normal = vector2::GetNormal(tempVector);
}

Line Edge::toLine() const
{
	return Line{ parent->get_vertex_at_index(v1).toPoint(), parent->get_vertex_at_index(v2).toPoint() };
}

