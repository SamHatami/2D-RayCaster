#include "Edge.h"

#include "Vertex.h"

Edge::Edge(Vertex& v1, Vertex& v2, bool isInternal)
    : v1(v1)
    , v2(v2)
    , isInternal(isInternal)
    
{
	vector2 tempVector = vector2::PointsToVector2(v1.toPoint(), v2.toPoint());
	tempVector.Normalize();
	normal = vector2::GetNormal(tempVector);
}

Line Edge::toLine() const
{
	return Line{ v1.toPoint(), v1.toPoint() };
}


Edge& Edge::operator=(const Edge& other) {
    if (this == &other) {
        return *this;
    }
    v1 = other.v1;
    v2 = other.v2;
    isInternal = other.isInternal;
    normal = other.normal;
    return *this;
}

