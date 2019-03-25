#ifndef SHAPECIRCLE_H
#define SHAPECIRCLE_H

#include "Shapes/shape.h"

class ShapeCircle : public Shape
{
public:
    ShapeCircle();

    void Redraw(QPainter& painter);
    void Resize(QSize& new_size);
};

#endif // SHAPECIRCLE_H
