#include "hierarchy.h"
#include "ui_hierarchy.h"
#include "Entity/entity.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inspector.h"

#include "hierarchyentity.h"

#include "Managers/entitymanager.h"

#include "globals.h"

#include <QLabel>
#include <list>

Hierarchy::Hierarchy(MainWindow* mainwindow_, QWidget *parent) :
    QWidget(parent),
    mainwindow(mainwindow_),
    ui(new Ui::Hierarchy)
{
    ui->setupUi(this);
}

Hierarchy::~Hierarchy()
{
    delete ui;

    h_entities.clear();
}

void Hierarchy::UpdateUI()
{
    for(std::vector<HierarchyEntity*>::iterator it = h_entities.begin(); it != h_entities.end(); ++it)
    {
        (*it)->UpdateUI();
    }
}

void Hierarchy::on_buttonAddEntity_clicked()
{
    Entity* new_entity = EntityManager::Instance()->CreateEntity();

    std::string entity_name = "entity_" + std::to_string(EntityManager::Instance()->GetEntities().size() - 1);

    new_entity->SetName(entity_name);

    HierarchyEntity* new_entity_in_hierarchy = new HierarchyEntity(new_entity, this);

    ui->scrollLayout->addWidget(new_entity_in_hierarchy);

    h_entities.push_back(new_entity_in_hierarchy);

    UpdateUI();
}

void Hierarchy::on_buttonRemoveEntity_clicked()
{
    Entity* selectedEntity = EntityManager::Instance()->GetSelectedEntity();

    if (selectedEntity != nullptr)
    {
        for (std::vector<HierarchyEntity*>::iterator it = h_entities.begin(); it != h_entities.end(); ++it)
        {
            if ((*it)->GetEntity() == selectedEntity)
            {
                delete *it;
                h_entities.erase(it);

                break;
            }
        }

        EntityManager::Instance()->DestroyEntity(selectedEntity);
    }
}
