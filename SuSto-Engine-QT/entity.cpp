#include "entity.h"
#include "component.h"

#include "globals.h"

Entity::Entity()
{

}

Entity::~Entity()
{
    components.clear();
}

Component *Entity::AddComponent(component_type type_)
{
    Component* ret = nullptr;

    switch (type_)
    {
        case component_type::COMPONENT_TRANSFORM:
        {
            //ret = new C_Transform(this);
            SPOOKYLOG("Component -Transform- created");
        }
        break;
        case component_type::COMPONENT_SHAPE_RENDERER:
        {
            //ret = new C_ShapeRenderer(this);
            SPOOKYLOG("Component -Shape Renderer- created");
        }
        break;
        case component_type::COMPONENT_NULL:
        {
            SPOOKYLOG("Component of type null created");
        }
        break;
    }

    if (ret == nullptr)
        SPOOKYLOG("Component is null / not created");

    //components.push_back(ret);

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
