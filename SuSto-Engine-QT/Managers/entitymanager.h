#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>

#include "Entity/entity.h"

class EntityManager
{
private:
    EntityManager();
    void operator delete(void *) {}

public:
    static EntityManager* Instance()
    {
        if(instance == nullptr)
        {
            instance = new EntityManager();

            instance->Start();
        }

        return instance;
    }

    static void DestroyInstance()
    {
        if(instance != nullptr)
        {
            instance->CleanUp();

            delete instance;

            instance = nullptr;
        }
    }

    Entity* CreateEntity();
    void DestroyEntity(Entity*& entity);
    void DestroyAllEntities();

    std::vector<Entity*> GetEntities() {
        return entities;
    }

    Entity* GetSelectedEntity();
    void SetSelectedEntity(Entity* entity);

private:
    void Start();
    void CleanUp();

private:
    static EntityManager* instance;

    std::vector<Entity*> entities;
    Entity* selectedEntity = nullptr;
};

#endif // ENTITYMANAGER_H
