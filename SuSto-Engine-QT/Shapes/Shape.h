#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <qpainter.h>

enum ShapeType
{
    SHAPE_CIRCLE,

    SHAPE_NULL
};

class Shape
{
public:
    Shape(ShapeType type);

    virtual void Redraw(QPainter& painter) {};

    ShapeType GetType() const;

private:
    ShapeType type = ShapeType::SHAPE_NULL;
};

#endif // SHAPE_H
