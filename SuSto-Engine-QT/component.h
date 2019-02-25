#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

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
    Component(component_type type_, Entity* owner_);

    std::string GetCName() const;
    void SetCName(std::string new_name);

public:
    component_type type = component_type::COMPONENT_NULL;
    Entity* owner = nullptr;

private:
    std::string name = "";
};

#endif // COMPONENT_H
