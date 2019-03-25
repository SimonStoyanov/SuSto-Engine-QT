#include "entity.h"
#include "Components/component.h"

#include "Components/c_transform.h"
#include "Components/c_shape_renderer.h"

#include "globals.h"

Entity::Entity()
{
    transform = (C_Transform*) AddComponent(ComponentType::COMPONENT_TRANSFORM);
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

Component *Entity::AddComponent(ComponentType type_)
{
    Component* ret = nullptr;

    switch (type_)
    {
        case ComponentType::COMPONENT_TRANSFORM:
        {
            ret = new C_Transform(this);
            SPOOKYLOG("Component -Transform- created");
        }
        break;
        case ComponentType::COMPONENT_SHAPE_RENDERER:
        {
            ret = new C_ShapeRenderer(this);
            SPOOKYLOG("Component -Shape Renderer- created");
        }
        break;
        case ComponentType::COMPONENT_NULL:
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
        ret->CreateUI();
    }

    return ret;

}

C_Transform *Entity::GetTransform() const
{
    return transform;
}

void Entity::DestroyComponent(Component*& component)
{
    if(component != nullptr)
    {
        for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
        {
            if((*it) == component)
            {
                components.erase(it);
                break;
            }
        }

        component->DestroyUI();
        component->CleanUp();

        delete component;
        component = nullptr;
    }
}

std::vector<Component *> Entity::GetComponents() const
{
    return components;
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
    for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
    {
        (*it)->CleanUp();

        delete (*it);
    }

    components.clear();
}
