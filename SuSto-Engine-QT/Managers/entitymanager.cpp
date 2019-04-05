#include "entitymanager.h"
#include "Events/selectentitychange.h"
#include "eventmanager.h"
#include "globals.h"
#include "Entity/Components/component.h"
#include "Entity/Components/c_transform.h"
#include "Entity/Components/c_shape_renderer.h"
#include "Managers/jsonmanager.h"
#include "functions.h"
#include "Entity/entityabstraction.h"

EntityManager* EntityManager::instance = nullptr;

EntityManager::EntityManager()
{
    base_instance_uid = GetUIDRandomHexadecimal();
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
    Entity* ret = new Entity(GetUIDRandomHexadecimal(), base_instance_uid);

    ret->Start();

    entities.push_back(ret);

    return ret;
}

Entity *EntityManager::CreateEntity(const std::string &uid, const std::string &instance_uid)
{
    Entity* ret = new Entity(uid, instance_uid);

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
         if ((*it) == selectedEntity)
             SetSelectedEntity(nullptr);

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

std::vector<Entity *> EntityManager::DuplicateEntity(std::vector<Entity *> entity)
{
    std::vector<Entity*> ret;

    EntityAbstraction abs;
    abs.Abstract(entity);
    ret = abs.DeAbstract();

    return ret;
}

