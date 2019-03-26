#include "Entity/Components/component.h"
#include "Entity/entity.h"
#include "3rdParty/MathGeoLib/Math/float2.h"

Component::Component()
{

}

Component::Component(ComponentType t, const std::string& n, Entity* o, bool un, bool can_del)
{
    type = t;
    owner = o;
    name = n;
    unique = un;
    can_delete = can_del;
}

ComponentType Component::GetType() const
{
    return type;
}

Entity *Component::GetOwner() const
{
    return owner;
}

std::string Component::GetName() const
{
    return name;
}
