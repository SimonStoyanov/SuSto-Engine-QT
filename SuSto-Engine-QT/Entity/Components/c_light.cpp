#include "c_light.h"
#include "ui_light.h"
#include "globals.h"

C_Light::C_Light(Entity *owner) : Component (ComponentType::COMPONENT_LIGHT, "Light", owner, true)
{

}

void C_Light::Start()
{

}

void C_Light::Update()
{

}

void C_Light::CleanUp()
{

}

void C_Light::OnSaveAbstraction(DataAbstraction &abs)
{

}

void C_Light::OnLoadAbstraction(DataAbstraction &abs)
{

}

void C_Light::CreateUI()
{
    form = new Ui::Light();
    ui = new QWidget();
    form->setupUi(ui);

    form->ComboLightType->addItem("Ambient", LightType::AMBIENT_LIGHT);
    form->ComboLightType->addItem("Point", LightType::POINT_LIGHT);
    form->ComboLightType->addItem("Directional", LightType::DIRECTIONAL_LIGHT);

    connect(form->ComboLightType, SIGNAL(currentIndexChanged(const QString&)),
            this, SLOT(OnComboLightTypeChanges(const QString&)));

    form->ComboLightType->setCurrentIndex(0);

    connect(form->Intensity, SIGNAL(valueChanged(double)), this, SLOT(OnIntensityChanges(double)));

    form->Intensity->setValue(5);

    connect(form->ColorR, SIGNAL(valueChanged(int)), this, SLOT(OnColorChanges(int)));
    connect(form->ColorG, SIGNAL(valueChanged(int)), this, SLOT(OnColorChanges(int)));
    connect(form->ColorB, SIGNAL(valueChanged(int)), this, SLOT(OnColorChanges(int)));

    form->ColorR->setValue(255);
    form->ColorG->setValue(255);
    form->ColorB->setValue(255);
}

void C_Light::DestroyUI()
{
    delete ui;
}

void C_Light::UpdateUI()
{

}

QWidget *C_Light::GetUI() const
{
    return ui;
}

LightType C_Light::GetLightType() const
{
    return type;
}

float C_Light::GetLightIntensity() const
{
    return intensity;
}

float3 C_Light::GetLightColour() const
{
    return colour;
}

void C_Light::OnComboLightTypeChanges(const QString &new_shape)
{
    int data = form->ComboLightType->itemData(form->ComboLightType->currentIndex()).toInt();

    type = (LightType)data;
}

void C_Light::OnIntensityChanges(double val)
{
    intensity = val;
}

void C_Light::OnColorChanges(int val)
{
    colour.x = float(form->ColorR->value()) / 255.0f;
    colour.y = float(form->ColorG->value()) / 255.0f;
    colour.z = float(form->ColorB->value()) / 255.0f;
}
