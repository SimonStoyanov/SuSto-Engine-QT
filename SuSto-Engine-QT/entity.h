#ifndef ENTITY_H
#define ENTITY_H

#include <list>

class Component;
enum component_type;

class Entity
{
public:
    Entity();
    ~Entity();

    Component *AddComponent(component_type type_);

public:
    std::string GetName();
    void SetName(std::string name_);

private:
    std::string name = "";


    std::list<Component> components;
};

#endif // ENTITY_H