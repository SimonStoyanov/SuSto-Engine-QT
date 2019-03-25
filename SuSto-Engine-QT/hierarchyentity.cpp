#include "hierarchyentity.h"
#include "ui_hierarchyentity.h"
#include "Managers/entitymanager.h"
#include "Events/event.h"
#include "globals.h"
#include "Entity/entity.h"

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

Entity* HierarchyEntity::GetEntity()
{
    return parentEntity;
}

void HierarchyEntity::UpdateUI()
{
    if(parentEntity != nullptr)
    {
        ui->entityName->setText(parentEntity->GetName().c_str());
    }
}

void HierarchyEntity::on_entityName_clicked()
{
    EntityManager::Instance()->SetSelectedEntity(parentEntity);
}
