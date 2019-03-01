#include "hierarchy.h"
#include "ui_hierarchy.h"
#include "entity.h"
#include "hierarchyentity.h"

#include "globals.h"

#include <QLabel>

Hierarchy::Hierarchy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hierarchy)
{
    ui->setupUi(this);
}

Hierarchy::~Hierarchy()
{
    delete ui;

    entities.clear();
}

void Hierarchy::CreateEntityInHierarchy(Entity* entity, std::string name)
{
    HierarchyEntity *new_entity_in_hierarchy = new HierarchyEntity(entity);
    new_entity_in_hierarchy->SetName(name);
    ui->scrollLayout->addWidget(new_entity_in_hierarchy);
}

void Hierarchy::on_buttonAddEntity_clicked()
{
    Entity* new_entity = new Entity();

    std::string name = "entity_" + std::to_string(entities.size());

    new_entity->SetName(name);

    SPOOKYLOG(name + " created succesfully");

    entities.push_back(new_entity);

    CreateEntityInHierarchy(new_entity, name);
}

void Hierarchy::on_buttonRemoveEntity_clicked()
{

}
