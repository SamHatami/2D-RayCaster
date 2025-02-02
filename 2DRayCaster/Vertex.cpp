#include "Vertex.h"

Vertex::Vertex(float x, float y, uint32_t color)
    : x(x), y(y), color(color), internalNr(0), globalNr(0) {}

Point Vertex::toPoint() const {
    return Point(x, y);
}
