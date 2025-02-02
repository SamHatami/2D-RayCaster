#include "Polygon.h"



Polygon::Polygon(std::vector<Vertex>& vertices, std::vector<Edge>& edges)
	: vertices(vertices)
	, edges(edges){


	for (auto& edge : edges) {
		edge.parent = this;
	}

	for (auto& vertex : vertices) {
		vertex.parent = this;
	}
	//TODO:
	//Create boundingBox
	//Create center of mass = centerPoint


	//create_bounding_box();
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
	 return { edge.v1, edge.v2};
}

void Polygon::set_shadow(const Shadow& shadow)
{
	this->shadow = shadow;
}

Shadow& Polygon::get_shadow()
{
	return shadow;
}

void Polygon::set_vertices(const std::vector<Vertex>& vertices)
{
	this->vertices = vertices;
	for (auto& vertex : this->vertices) {
		vertex.parent = this;
	}
}

void Polygon::set_edges(const std::vector<Edge>& edges)
{
	this->edges = edges;
	for (auto& edge : this->edges) {
		edge.parent = this;
	}

}

void Polygon::create_bounding_box()
{

}

