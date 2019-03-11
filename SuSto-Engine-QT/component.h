#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class QWidget;
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

    virtual void Start(){}
    virtual void CleanUp(){}

    //virtual QWidget* GetUI() {return nullptr;}

    std::string GetCName() const;
    void SetCName(std::string new_name);

    component_type GetType() const;
    Entity *GetOwner() const;

public:

private:
    std::string name = "";

    component_type type = component_type::COMPONENT_NULL;
    Entity* owner = nullptr;
};

#endif // COMPONENT_H
