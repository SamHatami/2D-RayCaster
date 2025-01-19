#include "Wall.h"

Wall::Wall(int height, const Line& definition)
    : height(height)
    , definition(definition)
{
    vector2 tempVector = vector2::PointsToVector2(definition.start, definition.end);
    tempVector.Normalize();
    normal = vector2::GetNormal(tempVector);
}