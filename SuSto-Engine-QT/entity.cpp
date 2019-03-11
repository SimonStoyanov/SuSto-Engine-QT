#include "entity.h"
#include "component.h"

#include "Components/c_transform.h"
#include "Components/c_shape_renderer.h"

#include "globals.h"

Entity::Entity()
{

}

Entity::~Entity()
{
    components.clear();
}

void Entity::Start()
{

}

void Entity::CleanUp()
{
    DestroyAllComponents();
}

Component *Entity::AddComponent(component_type type_)
{
    Component* ret = nullptr;

    switch (type_)
    {
        case component_type::COMPONENT_TRANSFORM:
        {
            ret = new C_Transform(this);
            SPOOKYLOG("Component -Transform- created");
        }
        break;
        case component_type::COMPONENT_SHAPE_RENDERER:
        {
            ret = new C_ShapeRenderer(this);
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
    else
    {
        components.push_back(ret);

        ret->Start();
    }

    return ret;

}

void Entity::DestroyComponent(Component*& component)
{
    if(component != nullptr)
    {
        for(std::list<Component*>::iterator it = components.begin(); it != components.end(); ++it)
        {
            if((*it) == component)
            {
                components.erase(it);
                break;
            }
        }

        component->CleanUp();

        delete component;
        component = nullptr;
    }
}

std::string Entity::GetName()
{
    return name;
}

void Entity::SetName(std::string name_)
{
    name = name_;
}

void Entity::DestroyAllComponents()
{
    for(std::list<Component*>::iterator it = components.begin(); it != components.end(); ++it)
    {
        (*it)->CleanUp();

        delete (*it);
    }

    components.clear();
}
