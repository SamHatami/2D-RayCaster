#pragma once
#include <vector>
#include "Geometry.h"
#include "Edge.h"
#include "Vertex.h"

struct Point;
struct Vertex;
struct Edge;

class Polygon //-> TODO: create interface IShape
{
private:
	std::vector<Vertex> vertices;
	std::vector<Edge> edges;
	BoundingBox boundingBox;
	Point centerPoint; //local?
	Point position; //Global

public:
	Polygon(std::vector<Vertex>& vertices, std::vector<Edge>& edges, BoundingBox& boundingBox,
		Point& centerPoint, Point& position);	

	std::vector<Vertex&> getBoundaryPoints();
};
