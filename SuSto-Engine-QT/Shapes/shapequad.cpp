#include "shapequad.h"

ShapeQuad::ShapeQuad() : Shape(ShapeType::SHAPE_QUAD)
{

}

void ShapeQuad::Redraw(QPainter &painter)
{
    painter.setPen(pen);
    painter.setBrush(brush);

    float w = size.x * 2.0f;
    float h = size.y * 2.0f;

    QRect circle_rect(pos.x - size.x, pos.y - size.y, w, h);

    painter.drawRect(circle_rect);
}

void ShapeQuad::Resize(QSize &new_size)
{

}
