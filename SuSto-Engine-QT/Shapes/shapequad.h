#ifndef SHAPEQUAD_H
#define SHAPEQUAD_H

#include "Shapes/shape.h"

class ShapeQuad : public Shape
{
public:
    ShapeQuad();

    void Redraw(QPainter& painter);
    void Resize(QSize& new_size);
};

#endif // SHAPEQUAD_H
