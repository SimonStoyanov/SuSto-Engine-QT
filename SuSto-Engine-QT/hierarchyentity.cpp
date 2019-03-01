#include "hierarchyentity.h"
#include "ui_hierarchyentity.h"

#include "entity.h"

HierarchyEntity::HierarchyEntity(Entity* entity, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::HierarchyEntity)
{
    ui->setupUi(this);
    parentEntity = entity;
}

HierarchyEntity::~HierarchyEntity()
{
    delete ui;
}

void HierarchyEntity::SetName(std::string name)
{
    ui->entityName->setText(name.c_str());
}
