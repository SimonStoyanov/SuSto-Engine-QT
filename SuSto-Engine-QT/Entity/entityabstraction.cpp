#include "entityabstraction.h"
#include "entity.h"
#include "Managers/jsonmanager.h"
#include "Entity/Components/component.h"
#include "Functions.h"
#include "Managers/entitymanager.h"
#include "Entity/Components/c_transform.h"
#include "globals.h"

EntityAbstraction::EntityAbstraction()
{

}

EntityAbstraction::~EntityAbstraction()
{

}

void EntityAbstraction::Abstract(const std::vector<Entity *>& to_abstract)
{
    Clear();

    std::vector<Entity*> all_to_abstract;

    for (std::vector<Entity*>::const_iterator it = to_abstract.cbegin(); it != to_abstract.cend(); ++it)
        all_to_abstract.push_back((*it));

    std::vector<Entity*> entities_indexed;

    while (all_to_abstract.size() > 0)
    {
        Entity* curr_go = *all_to_abstract.begin();

        entities_indexed.push_back(curr_go);

        //std::vector<GameObject*> childs = curr_go->GetChilds();

        //if(curr_go->GetChildsCount() > 0)
            //all_to_abstract.insert(all_to_abstract.end(), childs.begin(), childs.end());

        all_to_abstract.erase(all_to_abstract.begin());
    }

    for (std::vector<Entity*>::iterator it = entities_indexed.begin(); it != entities_indexed.end(); ++it)
    {
        Entity* curr_entity = (*it);

        EntityAbstractionRelation curr_relation;

        curr_relation.uid = curr_entity->GetUID();

        std::string parent_uid = "";

        //GameObject* parent_go = curr_go->GetParent();

        //if (parent_go != nullptr)
            //parent_uid = parent_go->GetUID();

        curr_relation.parent_uid = parent_uid;

        std::vector<Component*> components = curr_entity->GetComponents();

        curr_entity->OnSaveAbstraction(curr_relation.e_abstraction);

        curr_relation.e_abstraction.AddInt("components_count", components.size());

        for (std::vector<Component*>::iterator com = components.begin(); com != components.end(); ++com)
        {
            Component* comp = (*com);

            DataAbstraction component_abstraction;

            component_abstraction.AddInt("type", comp->GetType());

            comp->OnSaveAbstraction(component_abstraction);

            curr_relation.components_abstraction.push_back(component_abstraction);
        }

        relations.push_back(curr_relation);
     }

     abstracted = true;
}

std::vector<Entity *> EntityAbstraction::DeAbstract()
{
    std::vector<Entity*> ret;

    ret.reserve(relations.size());

    std::string instance_uid = GetUIDRandomHexadecimal();

    class TmpEntityReference
    {
    public:
        EntityAbstractionRelation abstraction;
        Entity* entity = nullptr;
    };

    std::vector<TmpEntityReference> tmp_references;
    tmp_references.reserve(relations.size());

    if (abstracted)
    {
        for (std::vector<EntityAbstractionRelation>::iterator it = relations.begin(); it != relations.end(); ++it)
        {
            Entity* curr_entity = EntityManager::Instance()->CreateEntity((*it).uid, instance_uid);
            ret.push_back(curr_entity);

            curr_entity->OnLoadAbstraction((*it).e_abstraction);

            TmpEntityReference tmp_ref;
            tmp_ref.entity = curr_entity;
            tmp_ref.abstraction = (*it);

            tmp_references.push_back(tmp_ref);
        }

        for (std::vector<TmpEntityReference>::iterator it = tmp_references.begin(); it != tmp_references.end(); ++it)
        {
            Entity* curr_entity = (*it).entity;

            if ((*it).abstraction.parent_uid.compare("") != 0)
            {
                for (std::vector<TmpEntityReference>::iterator ch = tmp_references.begin(); ch != tmp_references.end(); ++ch)
                {
                    if ((*it).abstraction.parent_uid.compare((*ch).abstraction.uid) == 0)
                    {
                        //curr_go->SetParent((*ch).go);
                        break;
                    }
                }
            }

            std::vector<DataAbstraction> components_abstractions = (*it).abstraction.components_abstraction;

            for (std::vector<DataAbstraction>::iterator com = components_abstractions.begin(); com != components_abstractions.end(); ++com)
            {
                int type = (*com).GetInt("type", -1);

                if (type > -1)
                {
                    if (type == 0)
                    {
                        curr_entity->GetTransform()->OnLoadAbstraction((*com));
                    }
                    else
                    {
                        Component* new_component = curr_entity->AddComponent(static_cast<ComponentType>(type));
                        new_component->OnLoadAbstraction((*com));
                    }
                }
            }
        }
    }

    return ret;
}

bool EntityAbstraction::Serialize(const std::string &path, const std::string &name, const std::string &extension)
{
    std::string filepath = path + name + "." + extension;

    return Serialize(filepath);
}

bool EntityAbstraction::Serialize(const std::string &filepath)
{
    bool ret = false;

    if (abstracted)
    {
        JsonDoc* doc = JsonManager::Instance()->CreateJSON(filepath.c_str());

        if (doc != nullptr)
        {
            doc->MoveToRoot();

            doc->SetNumber("entities_count", relations.size());

            int go_count = 0;
            for (std::vector<EntityAbstractionRelation>::iterator it = relations.begin(); it != relations.end(); ++it)
            {
                doc->MoveToRoot();

                std::string curr_go_section = "entity_" + std::to_string(go_count++);
                doc->AddSection(curr_go_section);

                if (doc->MoveToSection(curr_go_section))
                {
                    doc->SetString("uid", (*it).uid.c_str());
                    doc->SetString("parent_uid", (*it).parent_uid.c_str());

                    JsonDoc go_node = doc->GetNode();

                    (*it).e_abstraction.Serialize(go_node);

                    doc->SetArray("components");

                    int component_count = 0;

                    for (std::vector<DataAbstraction>::iterator c = (*it).components_abstraction.begin(); c != (*it).components_abstraction.end(); ++c)
                    {
                         JsonDoc comp_node = doc->GetNode();

                         comp_node.AddSectionToArray("components");

                         if (comp_node.MoveToSectionFromArray("components", component_count++))
                         {
                             (*c).Serialize(comp_node);
                         }
                     }
                 }
             }

             doc->Save();
             doc->MoveToRoot();

             JsonManager::Instance()->UnloadJSON(doc);

            ret = true;
        }
    }

    return ret;
}

bool EntityAbstraction::DeSerialize(const std::string &filepath)
{
    bool ret = false;

    Clear();

    JsonDoc* doc = JsonManager::Instance()->LoadJSON(filepath.c_str());

    if (doc != nullptr)
    {
        int game_objects_count = doc->GetNumber("entities_count", 0);

        for (int i = 0; i < game_objects_count; ++i)
        {
            doc->MoveToRoot();

            std::string curr_go_section = "entity_" + std::to_string(i);

            if (doc->MoveToSection(curr_go_section))
            {
                EntityAbstractionRelation curr_relation;

                curr_relation.uid = doc->GetString("uid", "");
                curr_relation.parent_uid = doc->GetString("parent_uid", "");

                JsonDoc go_node = doc->GetNode();

                if (curr_relation.uid.compare("") != 0)
                {
                    curr_relation.e_abstraction.DeSerialize(go_node);

                    int components_count = go_node.GetArrayCount("components");

                    for (int c = 0; c < components_count; ++c)
                    {
                        JsonDoc comp_node = go_node.GetNode();

                        if (comp_node.MoveToSectionFromArray("components", c))
                        {
                            DataAbstraction comp_data;
                            comp_data.DeSerialize(comp_node);

                            curr_relation.components_abstraction.push_back(comp_data);
                        }
                    }
                }

                relations.push_back(curr_relation);
            }
        }

        abstracted = true;
        ret = true;

        JsonManager::Instance()->UnloadJSON(doc);
    }


    return ret;
}

void EntityAbstraction::Clear()
{
    abstracted = false;
    relations.clear();
}

EntityAbstractionRelation::EntityAbstractionRelation()
{

}
