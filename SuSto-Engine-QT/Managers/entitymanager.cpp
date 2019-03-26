#include "entitymanager.h"
#include "Events/selectentitychange.h"
#include "eventmanager.h"
#include "globals.h"
#include "Entity/Components/component.h"

EntityManager* EntityManager::instance = nullptr;

EntityManager::EntityManager()
{

}

void EntityManager::UpdateAllEntities()
{
    for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        (*it)->Update();
    }
}

Entity* EntityManager::CreateEntity()
{
    Entity* ret = new Entity();

    ret->Start();

    entities.push_back(ret);

    return ret;
}

void EntityManager::DestroyEntity(Entity*& entity)
{
    if(entity != nullptr)
    {
        for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
        {
            if((*it) == entity)
            {
                entities.erase(it);
                break;
            }
        }

        if (entity == selectedEntity)
            SetSelectedEntity(nullptr);

        entity->CleanUp();
        delete entity;
        entity = nullptr;
    }
}

void EntityManager::DestroyAllEntities()
{
    for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        (*it)->CleanUp();
        delete (*it);
    }

    entities.clear();
}

std::vector<Entity *> EntityManager::GetEntities()
{
    return entities;
}

Entity *EntityManager::GetSelectedEntity()
{
    return selectedEntity;
}

void EntityManager::SetSelectedEntity(Entity* entity)
{
    Entity* last_selected_entity = selectedEntity;

    selectedEntity = entity;

    if(last_selected_entity != entity)
    {
        SelectEntityChange* ev = new SelectEntityChange(selectedEntity);
        EventManager::Instance()->SendEvent(ev);
    }
}

void EntityManager::Start()
{
    AddComponentType(ComponentType::COMPONENT_TRANSFORM, "Transform");
    AddComponentType(ComponentType::COMPONENT_SHAPE_RENDERER, "Shape Renderer");
}

void EntityManager::CleanUp()
{
    DestroyAllEntities();
}

void EntityManager::AddComponentType(ComponentType type, const std::string &component_name)
{
    component_types[type] = component_name;
}

ComponentType EntityManager::GetComponentTypeByComponentName(const std::string &component_name) const
{
    ComponentType ret = ComponentType::COMPONENT_NULL;

    for(std::map<ComponentType, std::string>::const_iterator it = component_types.begin(); it != component_types.end(); ++it)
    {
        if((*it).second.compare(component_name) == 0)
        {
            ret = (*it).first;
            break;
        }
    }

    return ret;
}

std::map<ComponentType, std::string> EntityManager::GetAllComponentTypes() const
{
    return component_types;
}
