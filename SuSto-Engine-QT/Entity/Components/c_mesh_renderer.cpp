#include "c_mesh_renderer.h"
#include "ui_meshrenderer.h"
#include "Managers/meshmanager.h"
#include "Managers/eventmanager.h"
#include <functional>
#include "Events/event.h"

C_MeshRenderer::C_MeshRenderer(Entity *owner) : Component (ComponentType::COMPONENT_MESH_RENDERER, "Mesh renderer", owner, true)
{

}

void C_MeshRenderer::Start()
{
    EventManager::Instance()->Subscribe(std::bind(&C_MeshRenderer::OnEvent, this, std::placeholders::_1), EventType::EVENT_MESH_LOADED);
}

void C_MeshRenderer::Update()
{

}

void C_MeshRenderer::CleanUp()
{
    EventManager::Instance()->UnSuscribe(std::bind(&C_MeshRenderer::OnEvent, this, std::placeholders::_1), EventType::EVENT_MESH_LOADED);
}

void C_MeshRenderer::OnSaveAbstraction(DataAbstraction &abs)
{

}

void C_MeshRenderer::OnLoadAbstraction(DataAbstraction &abs)
{

}

void C_MeshRenderer::CreateUI()
{
    form = new Ui::MeshRenderer();
    ui = new QWidget();
    form->setupUi(ui);

    connect(form->MeshComboBoxSelector, SIGNAL(currentIndexChanged(const QString&)),
            this, SLOT(OnSelectedMeshChanges(const QString&)));

    UpdateMeshComboBox();
}

void C_MeshRenderer::DestroyUI()
{
    delete ui;
}

void C_MeshRenderer::UpdateUI()
{
    UpdateMeshComboBox();
}

QWidget *C_MeshRenderer::GetUI() const
{
    return ui;
}

void C_MeshRenderer::SetMesh(Mesh *m)
{
    mesh = m;

    if(mesh != nullptr)
    {
        QString text = QString::fromStdString(mesh->GetFilePathPlusName());
        form->MeshComboBoxSelector->setCurrentText(text);
    }
    else
    {
        form->MeshComboBoxSelector->setCurrentText("");
    }
}

Mesh *C_MeshRenderer::GetMesh() const
{
    return mesh;
}

void C_MeshRenderer::OnEvent(Event* ev)
{
    if(ev->GetType() == EventType::EVENT_MESH_LOADED)
    {
        UpdateUI();
    }
}

void C_MeshRenderer::UpdateMeshComboBox()
{
    std::vector<Mesh*> meshes = MeshManager::Instance()->GetAllMeshes();

    QString selected = form->MeshComboBoxSelector->itemText(form->MeshComboBoxSelector->currentIndex());

    form->MeshComboBoxSelector->clear();

    for(std::vector<Mesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it)
    {
        QString text = QString::fromStdString((*it)->GetFilePathPlusName());
        form->MeshComboBoxSelector->addItem(text, text);
    }

    form->MeshComboBoxSelector->setCurrentText(selected);
}

void C_MeshRenderer::OnSelectedMeshChanges(const QString& new_shape)
{
    mesh = nullptr;

    if(form->MeshComboBoxSelector->count() > 0)
    {
        QString curr_val = form->MeshComboBoxSelector->itemText(form->MeshComboBoxSelector->currentIndex());

        mesh = MeshManager::Instance()->GetLoadedMeshFromFilepathPlusName(curr_val.toStdString());

    }

    if(mesh != nullptr)
    {
        QString text = QString::fromStdString(mesh->GetFilePath());

        form->MeshName->setText(text);
    }
    else
    {
        form->MeshName->setText("'not selected'");
    }
}
