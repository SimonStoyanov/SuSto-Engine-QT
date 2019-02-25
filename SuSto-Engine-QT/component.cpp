#include "component.h"
#include "entity.h"

Component::Component()
{

}

Component::Component(component_type type_, Entity owner_) : type(type_), owner(&owner_)
{
}
