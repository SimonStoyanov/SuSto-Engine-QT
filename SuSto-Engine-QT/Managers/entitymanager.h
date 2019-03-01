#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>

#include "entity.h"

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

private:
    void Start();
    void CleanUp();

private:
    static EntityManager* instance;

    std::vector<Entity*> entities;
};

#endif // ENTITYMANAGER_H
