#include "Vertex.h"

Vertex::Vertex(float x, float y, uint32_t color, Polygon* parent)
    : x(x), y(y), color(color), parent(parent), internalNr(0), globalNr(0) {}

point Vertex::toPoint() const {
    return point(x, y);
}
