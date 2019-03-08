#include "hierarchy.h"
#include "ui_hierarchy.h"
#include "entity.h"
#include "mainwindow.h"
#include "inspector.h"

#include "hierarchyentity.h"

#include "Managers/entitymanager.h"

#include "globals.h"

#include <QLabel>

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

    entities.clear();
}

void Hierarchy::SetSelected(HierarchyEntity *selected)
{
    selectedEntity = selected;

    mainwindow->GetInspector()->SelectEntity(selected->GetParent());
}

void Hierarchy::UpdateSelectedEntity()
{
    Inspector* inspector = mainwindow->GetInspector();

    selectedEntity->SetName(inspector->GetEntityName());
}

void Hierarchy::CreateEntityInHierarchy(Entity* entity, std::string name)
{
    HierarchyEntity *new_entity_in_hierarchy = new HierarchyEntity(entity, this);
    new_entity_in_hierarchy->SetName(name);
    ui->scrollLayout->addWidget(new_entity_in_hierarchy);
}

void Hierarchy::on_buttonAddEntity_clicked()
{
    Entity* new_entity = EntityManager::Instance()->CreateEntity();
    new_entity->SetName("entity_" + std::to_string(EntityManager::Instance()->GetEntities().size() - 1));

    CreateEntityInHierarchy(new_entity, new_entity->GetName());
}

void Hierarchy::on_buttonRemoveEntity_clicked()
{

}
