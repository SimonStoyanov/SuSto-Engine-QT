#include "Entity/Components/c_transform.h"
#include "Entity/entity.h"
#include "Entity/Components/component.h"
#include "QWidget"
#include "ui_transform.h"
#include "globals.h"

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
}

void C_Transform::DestroyUI()
{
    delete form;
}

void C_Transform::UpdateUI()
{
    if(ui != nullptr)
    {

    }
}

QWidget *C_Transform::GetUI() const
{
    return ui;
}

void C_Transform::SetPos(const float2 &set)
{
    pos = set;
}

float2 C_Transform::GetPos() const
{
    return pos;
}

void C_Transform::SetScale(const float2 &set)
{
    scale = set;
}

float2 C_Transform::GetScale() const
{
    return scale;
}

void C_Transform::OnUIValueChanged(double val)
{
    SetPos(float2(form->posx->value(), form->posy->value()));
    SetScale(float2(form->sclx->value(), form->scly->value()));
}
