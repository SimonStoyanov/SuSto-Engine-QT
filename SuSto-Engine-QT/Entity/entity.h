#ifndef ENTITY_H
#define ENTITY_H

#include <list>
#include <vector>
#include "Managers/jsonmanager.h"

class Component;
enum ComponentType;

class C_Transform;

class Entity
{
    friend class EntityManager;
    friend class EntityAbstraction;

private:
    Entity(const std::string& uid, const std::string& instance_uid);
    ~Entity();
    void operator delete(void *) {}

    void Start();
    void Update();
    void CleanUp();

    void OnSaveAbstraction(DataAbstraction& abs);
    void OnLoadAbstraction(DataAbstraction& abs);

public:
    Component *AddComponent(ComponentType type_);
    void DestroyComponent(Component*& component);
    Component* GetComponent(ComponentType type);
    std::vector<Component *> GetComponents() const;

    C_Transform* GetTransform() const;

    std::string GetName();
    void SetName(std::string name_);

    std::string GetUID() const;
    std::string GetInstanceUID() const;

private:
    void UpdateAllComponents();
    void DestroyAllComponents();

    void CallOnComponentAdded(Component* call);
    void CallOnComponentRemoved(Component* call);

private:
    std::string name = "";
    std::string uid = "";
    std::string instance_uid = "";

    C_Transform* transform = nullptr;

    std::vector<Component*> components;
};

#endif // ENTITY_H
