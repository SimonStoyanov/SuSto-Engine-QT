#include "hierarchy.h"
#include "ui_hierarchy.h"
#include "Entity/entity.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inspector.h"
#include "UI/uiutils.h"
#include "Entity/entityabstraction.h"
#include "globals.h"
#include "hierarchyentity.h"
#include "QFileDialog"
#include "Renderers/texture.h"
#include "Managers/texturemanager.h"

#include "Managers/entitymanager.h"
#include "Managers/meshmanager.h"

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

void Hierarchy::UpdateEntitiesUI()
{
    UIUtils::RemoveWidgetsFromLayout(ui->scrollLayout);

    h_entities.clear();

    std::vector<Entity*> entities = EntityManager::Instance()->GetEntities();

    for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        HierarchyEntity* new_entity_in_hierarchy = new HierarchyEntity((*it), this);
        ui->scrollLayout->addWidget(new_entity_in_hierarchy);
        h_entities.push_back(new_entity_in_hierarchy);
    }
}

void Hierarchy::NewScene()
{
    EntityManager::Instance()->DestroyAllEntities();

    UpdateEntitiesUI();
    UpdateUI();
}

void Hierarchy::SaveScene()
{
    QString fileName = QFileDialog::getSaveFileName(this, ("Save Scene"), "scene_name", ("Scenes (*.spookyscene)"));

    std::vector<Entity*> entities = EntityManager::Instance()->GetEntities();

    EntityAbstraction abs;
    abs.Abstract(entities);

    abs.Serialize(fileName.toStdString());

    SPOOKYLOG(fileName.toStdString());

}

void Hierarchy::LoadScene()
{
    QString fileName = QFileDialog::getOpenFileName(this, ("Load Scene"), "scene_name", ("Scenes (*.spookyscene)"));

    EntityAbstraction abs;
    bool loaded = abs.DeSerialize(fileName.toStdString());

    if(loaded)
    {
        EntityManager::Instance()->DestroyAllEntities();

        abs.DeAbstract();
    }

    UpdateEntitiesUI();
    UpdateUI();
}

void Hierarchy::LoadModel()
{
    QString fileName = QFileDialog::getOpenFileName(this, ("Load Scene"), "scene_name", (""));

    SPOOKYLOG("Loading: " + fileName.toStdString());

    std::vector<Entity*> new_entity = EntityManager::Instance()->LoadModel(fileName.toStdString());

    for(std::vector<Entity*>::iterator it = new_entity.begin(); it != new_entity.end(); ++it)
    {
        HierarchyEntity* new_entity_in_hierarchy = new HierarchyEntity((*it), this);

        ui->scrollLayout->addWidget(new_entity_in_hierarchy);

        h_entities.push_back(new_entity_in_hierarchy);
    }

    UpdateEntitiesUI();
    UpdateUI();
}

void Hierarchy::LoadMesh()
{
    QString fileName = QFileDialog::getOpenFileName(this, ("Load Mesh"), "mesh", (""));

    std::vector<Mesh*> loaded_meshes = MeshManager::Instance()->LoadMesh(fileName.toStdString());

    for(std::vector<Mesh*>::iterator it = loaded_meshes.begin(); it != loaded_meshes.end(); ++it)
    {
        MeshManager::Instance()->LoadToVRAM((*it));
    }
}

void Hierarchy::LoadTexture()
{
    QString fileName = QFileDialog::getOpenFileName(this, ("Load Texture"), "texture", (""));

    Texture* loaded_texture = TextureManager::Instance()->LoadTexture(fileName.toStdString());

    if(loaded_texture != nullptr)
    {
        TextureManager::Instance()->LoadToVRAM(loaded_texture);
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

void Hierarchy::DuplicateEntity()
{
    Entity* selectedEntity = EntityManager::Instance()->GetSelectedEntity();

    if(selectedEntity != nullptr)
    {
        std::vector<Entity*> entities;
        entities.push_back(selectedEntity);

        EntityManager::Instance()->DuplicateEntity(entities);
    }

    UpdateEntitiesUI();
    mainwindow->GetInspector()->UpdateUI();
}

