#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

enum component_type
{
    COMPONENT_TRANSFORM,
    COMPONENT_SHAPE_RENDERER,

    COMPONENT_NULL
};

class Component
{
public:
    Component();
    Component(component_type type_, Entity owner_);

private:
    component_type type = component_type::COMPONENT_NULL;
    Entity* owner = nullptr;
};

#endif // COMPONENT_H
