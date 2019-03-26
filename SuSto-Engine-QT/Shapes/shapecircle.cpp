#include "shapecircle.h"
#include "3rdParty/MathGeoLib/Math/float2.h"

ShapeCircle::ShapeCircle() : Shape(ShapeType::SHAPE_CIRCLE)
{
    SetSize(float2(20, 20));

    SetFillColor(QColor::fromRgb(0, 0, 0));

    SetStrokeThickness(4);
    SetStrokeColor(QColor::fromRgb(0, 0, 0));
    SetStrokeStyle(Qt::PenStyle::DashLine);
}

void ShapeCircle::Redraw(QPainter &painter)
{
    painter.setPen(pen);
    painter.setBrush(brush);

    float w = size.x * 2.0f;
    float h = size.y * 2.0f;

    QRect circle_rect(pos.x - size.x, pos.y - size.y, w, h);

    painter.drawEllipse(circle_rect);
}

void ShapeCircle::Resize(QSize &new_size)
{

}
