#include "Shapes/shape.h"
#include "Managers/shapemanager.h"

Shape::Shape(ShapeType t)
{
    type = t;
}

ShapeType Shape::GetType() const
{
    return type;
}

void Shape::SetFillColor(const QColor &color)
{
    brush.setColor(color);

    ShapeManager::Instance()->RepaintDrawingWidget();
}

void Shape::SetStrokeColor(const QColor &color)
{
    pen.setColor(color);

    ShapeManager::Instance()->RepaintDrawingWidget();
}

void Shape::SetStrockeThickness(float set)
{
    pen.setWidthF(set);

    ShapeManager::Instance()->RepaintDrawingWidget();
}

void Shape::SetStrokeStyle(Qt::PenStyle style)
{
    pen.setStyle(style);

    ShapeManager::Instance()->RepaintDrawingWidget();
}

QColor Shape::GetFillColor() const
{
    return brush.color();
}

QColor Shape::GetStrokeColor() const
{
    return pen.color();

}

float Shape::GetStrokeThickness() const
{
    return pen.widthF();
}

Qt::PenStyle Shape::GetStrockeStyle() const
{
    return pen.style();
}

void Shape::SetPos(const float2 &set)
{
    pos = set;

    ShapeManager::Instance()->RepaintDrawingWidget();
}

float2 Shape::GetPos() const
{
    return pos;
}

void Shape::SetSize(const float2 &set)
{
    size = set;

    ShapeManager::Instance()->RepaintDrawingWidget();
}

float2 Shape::GetSize() const
{
    return size;
}
