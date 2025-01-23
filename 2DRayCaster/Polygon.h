#pragma once
#include <vector>
#include "Geometry.h"
#include "Edge.h"
#include "Shadow.h"
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
	Shadow shadow;
	void CreateBoundingBox();

	//for simplicity vertices are in global coordinates
public:
	Polygon(std::vector<Vertex>& vertices, std::vector<Edge>& edges);
	const Vertex& get_vertex_at_index(size_t vertexNr);
	const std::vector<Edge>& get_all_edges() const;

	std::pair<const Vertex&, const Vertex&> get_edge_vertices(const Edge& edge) const;

	void set_shadow(const Shadow& shadow);
};
