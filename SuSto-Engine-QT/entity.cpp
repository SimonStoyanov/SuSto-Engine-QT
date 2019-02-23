#include "entity.h"

Entity::Entity()
{

}

Entity::~Entity()
{
    components.clear();
}

Component *Entity::AddComponent(component_type type_, std::string unique_id)
{
    Component* ret = nullptr;
    std::string new_id = unique_id;


    return ret;

}

std::string Entity::GetName()
{
    return name;
}

void Entity::SetName(std::string name_)
{
    name = name_;
}
