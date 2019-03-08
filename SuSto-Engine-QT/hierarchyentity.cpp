#include "hierarchyentity.h"
#include "ui_hierarchyentity.h"
#include "mainwindow.h"
#include "inspector.h"
#include "hierarchy.h"

#include "entity.h"

HierarchyEntity::HierarchyEntity(Entity* entity, Hierarchy* hierarchy_, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::HierarchyEntity),
    parentEntity(entity),
    hierarchy(hierarchy_)
{
    ui->setupUi(this);
}

HierarchyEntity::~HierarchyEntity()
{
    delete ui;
}

void HierarchyEntity::SetName(std::string name)
{
    ui->entityName->setText(name.c_str());
    parentEntity->SetName(name.c_str());
}

void HierarchyEntity::on_entityName_clicked()
{
    hierarchy->SetSelected(this);
}
