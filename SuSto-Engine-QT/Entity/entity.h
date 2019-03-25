#ifndef ENTITY_H
#define ENTITY_H

#include <list>
#include <vector>

class Component;
enum ComponentType;

class C_Transform;

class Entity
{
    friend class EntityManager;

private:
    Entity();
    ~Entity();
    void operator delete(void *) {}

    void Start();
    void CleanUp();

public:
    Component *AddComponent(ComponentType type_);
    void DestroyComponent(Component*& component);
    std::vector<Component *> GetComponents() const;

    C_Transform* GetTransform() const;

    std::string GetName();
    void SetName(std::string name_);

private:
    void DestroyAllComponents();

private:
    std::string name = "";
    C_Transform* transform = nullptr;

    std::vector<Component*> components;
};

#endif // ENTITY_H