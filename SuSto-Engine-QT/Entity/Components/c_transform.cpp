#include "Entity/Components/c_transform.h"
#include "Entity/entity.h"
#include "Entity/Components/component.h"
#include "QWidget"
#include "ui_transform.h"
#include "globals.h"
#include "Managers/jsonmanager.h"

C_Transform::C_Transform(Entity* owner) : Component(ComponentType::COMPONENT_TRANSFORM, "Transform", owner, true, false)
{

}

C_Transform::~C_Transform()
{

}

void C_Transform::Start()
{

}

void C_Transform::CleanUp()
{

}

void C_Transform::OnSaveAbstraction(DataAbstraction &abs)
{

}

void C_Transform::OnLoadAbstraction(DataAbstraction &abs)
{

    UpdateUI();
}

void C_Transform::OnComponentAdded(Component *comp)
{
    if(comp->GetType() == ComponentType::COMPONENT_SHAPE_RENDERER)
    {
        shape_renderer = (C_ShapeRenderer*)comp;
    }
}

void C_Transform::OnComponentRemoved(Component *comp)
{
    if(comp->GetType() == ComponentType::COMPONENT_SHAPE_RENDERER)
    {
        if((C_ShapeRenderer*)comp == shape_renderer)
            shape_renderer = nullptr;
    }
}

void C_Transform::CreateUI()
{
    form = new Ui::Transform();
    ui = new QWidget();
    form->setupUi(ui);

    connect(form->posx, SIGNAL(valueChanged(double)), this, SLOT(OnUIValueChanged(double)));
    connect(form->posy, SIGNAL(valueChanged(double)), this, SLOT(OnUIValueChanged(double)));
    connect(form->posz, SIGNAL(valueChanged(double)), this, SLOT(OnUIValueChanged(double)));

    connect(form->rotx, SIGNAL(valueChanged(double)), this, SLOT(OnUIValueChanged(double)));
    connect(form->roty, SIGNAL(valueChanged(double)), this, SLOT(OnUIValueChanged(double)));
    connect(form->rotz, SIGNAL(valueChanged(double)), this, SLOT(OnUIValueChanged(double)));

    connect(form->sclx, SIGNAL(valueChanged(double)), this, SLOT(OnUIValueChanged(double)));
    connect(form->scly, SIGNAL(valueChanged(double)), this, SLOT(OnUIValueChanged(double)));
    connect(form->sclz, SIGNAL(valueChanged(double)), this, SLOT(OnUIValueChanged(double)));

    form->sclx->setValue(1);
    form->scly->setValue(1);
    form->sclz->setValue(1);
}

void C_Transform::DestroyUI()
{
    delete form;
}

void C_Transform::UpdateUI()
{
    if(ui != nullptr)
    {
        float3 pos = GetPos();
        float3 scale = GetScale();

        form->posx->setValue(pos.x);
        form->posy->setValue(pos.y);
        form->posz->setValue(pos.z);

        form->rotx->setValue(rotation.x);
        form->roty->setValue(rotation.y);
        form->rotz->setValue(rotation.z);

        form->sclx->setValue(scale.x);
        form->scly->setValue(scale.y);
        form->sclz->setValue(scale.z);
    }
}

QWidget *C_Transform::GetUI() const
{
    return ui;
}

void C_Transform::SetPos(const float3 &set)
{
    pos = set;
}

float3 C_Transform::GetPos() const
{
    return pos;
}

void C_Transform::SetRotationDegrees(const float3 &set)
{
    rotation = set;
}

float3 C_Transform::GetRotationDegrees() const
{
    return rotation;
}

void C_Transform::SetScale(const float3 &set)
{
    scale = set;
}

float3 C_Transform::GetScale() const
{
    return scale;
}

void C_Transform::OnUIValueChanged(double val)
{
    SetPos(float3(form->posx->value(), form->posy->value(), form->posz->value()));
    SetRotationDegrees(float3(form->rotx->value(), form->roty->value(), form->rotz->value()));
    SetScale(float3(form->sclx->value(), form->scly->value(), form->sclz->value()));
}
