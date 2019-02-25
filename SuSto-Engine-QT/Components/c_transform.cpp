#include "c_transform.h"
#include "entity.h"
#include "component.h"

C_Transform::C_Transform(Entity* owner) : Component(component_type::COMPONENT_TRANSFORM, owner)
{

}

C_Transform::~C_Transform()
{

}
