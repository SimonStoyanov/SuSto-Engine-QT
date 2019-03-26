#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class QWidget;
class Entity;

enum ComponentType
{
    COMPONENT_TRANSFORM,
    COMPONENT_SHAPE_RENDERER,

    COMPONENT_NULL
};

class Component
{
public:
    Component();
    Component(ComponentType type_, const std::string& name, Entity* owner_, bool unique = false, bool can_delete = true);

    virtual void Start(){}
    virtual void CleanUp(){}

    virtual void CreateUI() {}
    virtual void DestroyUI() {}
    virtual void UpdateUI() {}
    virtual QWidget* GetUI() const {return nullptr;}


    ComponentType GetType() const;
    Entity *GetOwner() const;
    std::string GetName() const;

public:

private:
    std::string name = "";
    bool unique = false;
    bool can_delete = false;

    ComponentType type = ComponentType::COMPONENT_NULL;
    Entity* owner = nullptr;

    QWidget* ui = nullptr;
};

#endif // COMPONENT_H
