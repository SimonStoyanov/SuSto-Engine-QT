#include "entitymanager.h"

EntityManager* EntityManager::instance = nullptr;

EntityManager::EntityManager()
{

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

        entity->CleanUp();
        delete entity;
        entity = nullptr;
        if (entity == selectedEntity)
            selectedEntity = nullptr;
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

Entity *EntityManager::GetSelectedEntity()
{
    return selectedEntity;
}

void EntityManager::SetSelectedEntity(Entity *entity)
{
    selectedEntity = entity;
}

void EntityManager::Start()
{

}

void EntityManager::CleanUp()
{
    DestroyAllEntities();
}
