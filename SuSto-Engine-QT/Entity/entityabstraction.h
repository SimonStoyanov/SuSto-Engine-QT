#ifndef ENTITYABSTRACTION_H
#define ENTITYABSTRACTION_H

#include <string>
#include <vector>
#include "Managers/jsonmanager.h"

class Entity;
class DataAbstraction;

class EntityAbstractionRelation
{
    friend class EntityAbstraction;

public:
    EntityAbstractionRelation();

private:
    std::string uid;
    std::string parent_uid;
    DataAbstraction e_abstraction;
    std::vector<DataAbstraction> components_abstraction;
};

class EntityAbstraction
{
    friend class Entity;
    friend class EntityAbstractionRelation;

private:
    void operator delete(void *) {}

public:
    EntityAbstraction();
    ~EntityAbstraction();

    void Abstract(const std::vector<Entity*>& to_abstract);
    std::vector<Entity*> DeAbstract();

    bool Serialize(const std::string& path, const std::string& name, const std::string& extension);
    bool Serialize(const std::string& filepath);
    bool DeSerialize(const std::string& filepath);

    void Clear();

private:
    std::vector<EntityAbstractionRelation> relations;

    bool abstracted = false;
};

#endif // ENTITYABSTRACTION_H
