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
    Component(ComponentType type_, Entity* owner_);

    virtual void Start(){}
    virtual void CleanUp(){}

    virtual void CreateUI() {}
    virtual void DestroyUI() {}
    virtual void UpdateUI() {}
    virtual QWidget* GetUI() const {return nullptr;}


    std::string GetCName() const;
    void SetCName(std::string new_name);

    ComponentType GetType() const;
    Entity *GetOwner() const;

public:

private:
    std::string name = "";

    ComponentType type = ComponentType::COMPONENT_NULL;
    Entity* owner = nullptr;

    QWidget* ui = nullptr;
};

#endif // COMPONENT_H
