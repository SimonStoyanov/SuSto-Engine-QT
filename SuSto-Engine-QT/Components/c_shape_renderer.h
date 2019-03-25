#ifndef C_SHAPERENDERER_H
#define C_SHAPERENDERER_H

#include "component.h"

#include "Shapes/shape.h"

class C_ShapeRenderer : public Component
{
public:
    C_ShapeRenderer(Entity* owner);

    void CreateShape(ShapeType type);

private:
    Shape* curr_shape = nullptr;
};

#endif // C_SHAPERENDERER_H
