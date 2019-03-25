#include "Components/component.h"
#include "entity.h"
#include "3rdParty/MathGeoLib/Math/float2.h"

Component::Component()
{

}

Component::Component(ComponentType type_, Entity* owner_) : type(type_), owner(owner_)
{

}

ComponentType Component::GetType() const
{
    return type;
}

Entity *Component::GetOwner() const
{
    return owner;
}
