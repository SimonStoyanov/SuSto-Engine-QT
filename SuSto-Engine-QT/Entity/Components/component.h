#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "QWidget"
#include "Managers/jsonmanager.h"

class Entity;

enum ComponentType
{
    COMPONENT_TRANSFORM,
    COMPONENT_SHAPE_RENDERER,

    COMPONENT_NULL
};

class Component : public QWidget
{
    Q_OBJECT

public:
    explicit Component(ComponentType type_, const std::string& name, Entity* owner_, bool unique = false, bool can_delete = true);

    virtual void Start(){}
    virtual void Update(){}
    virtual void CleanUp(){}

    virtual void OnSaveAbstraction(DataAbstraction& abs){}
    virtual void OnLoadAbstraction(DataAbstraction& abs){}

    virtual void OnComponentAdded(Component* comp) {};
    virtual void OnComponentRemoved(Component* comp){};

    virtual void CreateUI() {}
    virtual void DestroyUI() {}
    virtual void UpdateUI() {}
    virtual QWidget* GetUI() const {return nullptr;}

    ComponentType GetType() const;
    Entity *GetOwner() const;
    std::string GetName() const;

    bool GetUnique() const;
    bool GetCanDelete() const;

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
