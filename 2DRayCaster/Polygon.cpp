#include "Polygon.h"
#include "Polygon.h"

Polygon::Polygon(std::vector<Vertex>& vertices, std::vector<Edge>& edges, BoundingBox& boundingBox,
	Point& centerPoint, Point& position)
	: vertices(vertices)
	, edges(edges)
	, boundingBox(boundingBox)
	, centerPoint(centerPoint)
	, position(position) {
}