#include "component.h"
#include "entity.h"

Component::Component()
{

}

Component::Component(component_type type_, Entity* owner_) : type(type_), owner(owner_)
{

}

component_type Component::GetType() const
{
    return type;
}

Entity *Component::GetOwner() const
{
    return owner;
}
