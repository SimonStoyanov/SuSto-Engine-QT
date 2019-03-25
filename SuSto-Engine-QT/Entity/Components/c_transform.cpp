#include "c_transform.h"
#include "entity.h"
#include "component.h"
#include "QWidget"
#include "ui_transform.h"

C_Transform::C_Transform(Entity* owner) : Component(ComponentType::COMPONENT_TRANSFORM, owner)
{

}

C_Transform::~C_Transform()
{

}

void C_Transform::CreateUI()
{
    form = new Ui::Transform();
    ui = new QWidget();
    form->setupUi(ui);
}

void C_Transform::DestroyUI()
{
    delete form;
}

void C_Transform::UpdateUI()
{

}

QWidget *C_Transform::GetUI() const
{
    return ui;
}
