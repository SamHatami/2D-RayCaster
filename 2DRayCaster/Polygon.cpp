#include "Polygon.h"

void Polygon::CreateBoundingBox()
{
	
}

Polygon::Polygon(std::vector<Vertex>& vertices, std::vector<Edge>& edges)
	: vertices(vertices)
	, edges(edges){

	//TODO:
	//Create boundingBox
	//Create center of mass = centerPoint


	CreateBoundingBox();
}

 const Vertex& Polygon::get_vertex_at_index(size_t vertexNr)
{
	return vertices.at(vertexNr);
}

const std::vector<Edge>& Polygon::get_all_edges() const
{
	return edges;
}

std::pair<const Vertex&, const Vertex&> Polygon::get_edge_vertices(const Edge& edge) const
{
	 return { vertices.at(edge.v1), vertices.at(edge.v2)};
}
