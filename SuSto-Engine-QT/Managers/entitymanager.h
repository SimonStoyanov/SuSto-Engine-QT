#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <map>

#include "Entity/entity.h"
#include "Entity/Components/component.h"

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
    std::vector<Entity*> GetEntities();

    Entity* GetSelectedEntity();
    void SetSelectedEntity(Entity* entity);

    ComponentType GetComponentTypeByComponentName(const std::string& component_name) const;
    std::map<ComponentType, std::string> GetAllComponentTypes() const;

private:
    void Start();
    void CleanUp();

    void AddComponentType(ComponentType type, const std::string& component_name);

private:
    static EntityManager* instance;

    std::vector<Entity*> entities;
    Entity* selectedEntity = nullptr;

    std::map<ComponentType, std::string> component_types;
};

#endif // ENTITYMANAGER_H
