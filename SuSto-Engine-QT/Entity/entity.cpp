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

void Entity::Update()
{
    UpdateAllComponents();
}

void Entity::CleanUp()
{
    DestroyAllComponents();
}

Component *Entity::AddComponent(ComponentType type)
{
    Component* ret = nullptr;

    switch (type)
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
        bool can_add = true;

        if(ret->GetUnique())
        {
            if(GetComponent(type) != nullptr)
                can_add = false;
        }

        if(can_add)
        {
            components.push_back(ret);

            ret->Start();
            ret->CreateUI();

            CallOnComponentAdded(ret);
        }
        else
        {
            delete ret;
            ret = nullptr;
        }
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
        if(component->GetCanDelete())
        {
            for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
            {
                if((*it) == component)
                {
                    components.erase(it);
                    break;
                }
            }

            CallOnComponentRemoved(component);

            component->DestroyUI();
            component->CleanUp();

            delete component;
            component = nullptr;
        }
    }
}

Component* Entity::GetComponent(ComponentType type)
{
    Component* ret = nullptr;

    for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
    {
        if((*it)->GetType() == type)
        {
            ret = (*it);
            break;
        }
    }

    return ret;
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

void Entity::UpdateAllComponents()
{
    for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
    {
        (*it)->Update();
    }
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

void Entity::CallOnComponentAdded(Component *call)
{
    for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
        (*it)->OnComponentAdded(call);
}

void Entity::CallOnComponentRemoved(Component *call)
{
    for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
        (*it)->OnComponentRemoved(call);
}
