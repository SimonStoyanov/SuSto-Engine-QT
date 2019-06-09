#include "c_material_renderer.h"
#include "ui_materialrenderer.h"
#include "Renderers/texture.h"
#include "Managers/texturemanager.h"
#include "Managers/eventmanager.h"

C_MaterialRenderer::C_MaterialRenderer(Entity *owner) : Component (ComponentType::COMPONENT_MATERIAL_RENDERER, "Material renderer", owner, false)
{

}

void C_MaterialRenderer::Start()
{
    EventManager::Instance()->Subscribe(std::bind(&C_MaterialRenderer::OnEvent, this, std::placeholders::_1), EventType::EVENT_TEXTURE_LOADED);
}

void C_MaterialRenderer::Update()
{

}

void C_MaterialRenderer::CleanUp()
{
    EventManager::Instance()->UnSuscribe(std::bind(&C_MaterialRenderer::OnEvent, this, std::placeholders::_1), EventType::EVENT_TEXTURE_LOADED);
}

void C_MaterialRenderer::OnSaveAbstraction(DataAbstraction &abs)
{

}

void C_MaterialRenderer::OnLoadAbstraction(DataAbstraction &abs)
{

}

void C_MaterialRenderer::CreateUI()
{
    form = new Ui::MaterialRenderer();
    ui = new QWidget();
    form->setupUi(ui);

    connect(form->DiffuseCombo, SIGNAL(currentIndexChanged(const QString&)),
            this, SLOT(OnSelectedDiffuseChange(const QString&)));

    connect(form->NormalCombo, SIGNAL(currentIndexChanged(const QString&)),
            this, SLOT(OnSelectedNormalChange(const QString&)));

    connect(form->HeightCombo, SIGNAL(currentIndexChanged(const QString&)),
            this, SLOT(OnSelectedHeightChange(const QString&)));
}

void C_MaterialRenderer::DestroyUI()
{
    delete ui;
}

void C_MaterialRenderer::UpdateUI()
{

}

QWidget *C_MaterialRenderer::GetUI() const
{
    return ui;
}

void C_MaterialRenderer::OnEvent(Event *ev)
{
    if(ev->GetType() == EventType::EVENT_TEXTURE_LOADED)
    {
        UpdateTexturesComboBoxes();
    }
}

void C_MaterialRenderer::UpdateTexturesComboBoxes()
{
    std::vector<Texture*> textures = TextureManager::Instance()->GetAllTextures();

    QString selected_diffuse = form->DiffuseCombo->itemText(form->DiffuseCombo->currentIndex());
    QString selected_normal = form->NormalCombo->itemText(form->NormalCombo->currentIndex());
    QString selected_height = form->HeightCombo->itemText(form->HeightCombo->currentIndex());

    form->DiffuseCombo->clear();
    form->NormalCombo->clear();
    form->HeightCombo->clear();

    for(std::vector<Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
    {
        QString text = QString::fromStdString((*it)->GetFilePath());

        form->DiffuseCombo->addItem(text, text);
        form->NormalCombo->addItem(text, text);
        form->HeightCombo->addItem(text, text);
    }

    form->DiffuseCombo->setCurrentText(selected_diffuse);
    form->NormalCombo->setCurrentText(selected_normal);
    form->HeightCombo->setCurrentText(selected_height);
}

void C_MaterialRenderer::OnSelectedDiffuseChange(const QString &new_shape)
{
    diffuse_texture = nullptr;

    if(form->DiffuseCombo->count() > 0)
    {
        QString curr_val = form->DiffuseCombo->itemText(form->DiffuseCombo->currentIndex());

        diffuse_texture = TextureManager::Instance()->GetLoadedTextureFromFilepath(curr_val.toStdString());

    }
}

void C_MaterialRenderer::OnSelectedNormalChange(const QString &new_shape)
{
    normal_texture = nullptr;

    if(form->NormalCombo->count() > 0)
    {
        QString curr_val = form->NormalCombo->itemText(form->NormalCombo->currentIndex());

        normal_texture = TextureManager::Instance()->GetLoadedTextureFromFilepath(curr_val.toStdString());

    }
}

void C_MaterialRenderer::OnSelectedHeightChange(const QString &new_shape)
{
    height_texture = nullptr;

    if(form->NormalCombo->count() > 0)
    {
        QString curr_val = form->HeightCombo->itemText(form->HeightCombo->currentIndex());

        height_texture = TextureManager::Instance()->GetLoadedTextureFromFilepath(curr_val.toStdString());
    }
}
