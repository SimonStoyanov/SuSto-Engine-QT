#ifndef ENTITY_H
#define ENTITY_H

#include <list>
#include <vector>

class Component;
enum component_type;

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
    Component *AddComponent(component_type type_);
    C_Transform* GetTransform() const;
    void DestroyComponent(Component*& component);

    std::string GetName();
    void SetName(std::string name_);

private:
    void DestroyAllComponents();

private:
    std::string name = "";
    C_Transform* transform = nullptr;

    std::list<Component*> components; 
};

#endif // ENTITY_H
