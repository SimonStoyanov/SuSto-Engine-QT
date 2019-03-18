#include "component.h"
#include "entity.h"
#include "3rdParty/MathGeoLib/Math/float2.h"

Component::Component()
{

}

Component::Component(component_type type_, Entity* owner_) : type(type_), owner(owner_)
{
    float2 a = float2(1 ,1);
}

component_type Component::GetType() const
{
    return type;
}

Entity *Component::GetOwner() const
{
    return owner;
}
