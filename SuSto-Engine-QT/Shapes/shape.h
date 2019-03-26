#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <qpainter.h>
#include "3rdParty/MathGeoLib/Math/float2.h"

enum ShapeType
{
    SHAPE_CIRCLE,
    SHAPE_QUAD,

    SHAPE_NULL
};

class Shape
{
public:
    Shape(ShapeType type);

    virtual void Redraw(QPainter& painter) {};
    virtual void Resize(QSize& new_size) {};

    ShapeType GetType() const;

    void SetFillColor(const QColor& color);
    void SetStrokeColor(const QColor& color);
    void SetStrokeThickness(float set);
    void SetStrokeStyle(Qt::PenStyle style);

    QColor GetFillColor() const;
    QColor GetStrokeColor() const;
    float GetStrokeThickness() const;
    Qt::PenStyle GetStrockeStyle() const;

    void SetPos(const float2& pos);
    float2 GetPos() const;

    void SetSize(const float2& size);
    float2 GetSize() const;

protected:
    QBrush brush;
    QPen pen;

    float2 pos = float2::zero;
    float2 size = float2::zero;

private:
    ShapeType type = ShapeType::SHAPE_NULL;  
};

#endif // SHAPE_H
