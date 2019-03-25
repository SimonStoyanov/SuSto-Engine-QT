#include "Shapes/shape.h"

Shape::Shape(ShapeType t)
{
    type = t;
}

ShapeType Shape::GetType() const
{
    return type;
}
