#include "hierarchyentity.h"
#include "ui_hierarchyentity.h"
#include "Managers/entitymanager.h"
#include "Events/event.h"

#include "entity.h"

HierarchyEntity::HierarchyEntity(Entity* entity, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::HierarchyEntity),
    parentEntity(entity)
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
    EntityManager::Instance()->SetSelectedEntity(parentEntity);
}
