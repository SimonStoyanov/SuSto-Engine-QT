#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <map>

#include "Entity/entity.h"
#include "Entity/Components/component.h"

class C_Light;

class EntityManager
{
    friend class AppManager;

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

    void UpdateAllEntities();

    Entity* CreateEntity();
    Entity *CreateEntity(const std::string& uid, const std::string& instance_uid);
    void DestroyEntity(Entity*& entity);
    void DestroyAllEntities();
    std::vector<Entity*> GetEntities();

    Entity* GetSelectedEntity();
    void SetSelectedEntity(Entity* entity);

    ComponentType GetComponentTypeByComponentName(const std::string& component_name) const;
    std::map<ComponentType, std::string> GetAllComponentTypes() const;

    std::vector<Entity*> DuplicateEntity(std::vector<Entity*> entity);

    std::vector<Entity*> LoadModel(const std::string& filepath);

private:
    void Start();
    void CleanUp();

    void AddComponentType(ComponentType type, const std::string& component_name);

private:
    std::string base_instance_uid;

    static EntityManager* instance;

    std::vector<Entity*> entities;
    Entity* selectedEntity = nullptr;

    std::map<ComponentType, std::string> component_types;
};

#endif // ENTITYMANAGER_H
