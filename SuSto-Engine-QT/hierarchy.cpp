#include "hierarchy.h"
#include "ui_hierarchy.h"
#include "entity.h"
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

void Hierarchy::SetSelected(HierarchyEntity *selected)
{
    mainwindow->GetInspector()->SelectEntity(selected->GetEntity());
}

void Hierarchy::UpdateSelectedEntity()
{
    Inspector* inspector = mainwindow->GetInspector();

    /*if (selectedEntity != nullptr)
        selectedEntity->SetName(inspector->GetEntityName());
    else
        inspector->SetEntityName("No entity selected");*/
}

void Hierarchy::CopyEntity()
{
    entityInClipboard = EntityManager::Instance()->GetSelectedEntity();
    if (entityInClipboard != nullptr){
        SPOOKYLOG("Selected entity: " + entityInClipboard->GetName());
        mainwindow->GetUI()->actionPaste->setEnabled(true);
    }
    else
    {
        SPOOKYLOG("Nothing selected");
    }
}

void Hierarchy::PasteEntity()
{
    if (entityInClipboard != nullptr)
    {
        Entity* new_entity = EntityManager::Instance()->CreateEntity();
        new_entity->SetName(entityInClipboard->GetName() + "_copy");

        CreateEntityInHierarchy(new_entity, new_entity->GetName());
    }
}

void Hierarchy::CreateEntityInHierarchy(Entity* entity, std::string name)
{
    HierarchyEntity *new_entity_in_hierarchy = new HierarchyEntity(entity, this);
    new_entity_in_hierarchy->SetName(name);
    ui->scrollLayout->addWidget(new_entity_in_hierarchy);
    h_entities.push_back(new_entity_in_hierarchy);
}

void Hierarchy::on_buttonAddEntity_clicked()
{
    Entity* new_entity = EntityManager::Instance()->CreateEntity();
    new_entity->SetName("entity_" + std::to_string(EntityManager::Instance()->GetEntities().size() - 1));

    CreateEntityInHierarchy(new_entity, new_entity->GetName());
}

void Hierarchy::on_buttonRemoveEntity_clicked()
{
    Entity* selectedEntity = EntityManager::Instance()->GetSelectedEntity();

    if (selectedEntity != nullptr)
    {
        for (std::list<HierarchyEntity*>::iterator it = h_entities.begin(); it != h_entities.end(); ++it)
        {
            if ((*it)->GetEntity() == selectedEntity)
            {
                if ((*it)->GetEntity() == entityInClipboard)
                    mainwindow->GetUI()->actionPaste->setEnabled(false);

                delete *it;
                h_entities.erase(it);
                EntityManager::Instance()->DestroyEntity(selectedEntity);
                UpdateSelectedEntity();

                return;
            }
        }
    }

    UpdateSelectedEntity();
}
