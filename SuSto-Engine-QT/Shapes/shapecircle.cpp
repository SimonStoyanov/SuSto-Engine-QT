#include "shapecircle.h"
#include "3rdParty/MathGeoLib/Math/float2.h"

ShapeCircle::ShapeCircle() : Shape(ShapeType::SHAPE_CIRCLE)
{

}

void ShapeCircle::Redraw(QPainter &painter)
{
    float2 pos = float2(0, 0);

    int radious = 60;

    // -------------

    QColor black_color = QColor::fromRgb(0, 0, 0);
    QColor white_color = QColor::fromRgb(255, 255, 255);

    QBrush brush;
    QPen pen;

    pen.setWidth(4);
    pen.setColor(black_color);
    pen.setStyle(Qt::PenStyle::DashLine);

    brush.setColor(white_color);

    painter.setPen(pen);
    painter.setBrush(brush);

    int w = radious * 2;
    int h = radious * 2;

    QRect circle_rect(pos.x, pos.y, w, h);

    painter.drawEllipse(circle_rect);
}

void ShapeCircle::Resize(QSize &new_size)
{

}
