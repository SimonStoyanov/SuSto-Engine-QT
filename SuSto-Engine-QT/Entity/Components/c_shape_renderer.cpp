#include "Entity/Components/c_shape_renderer.h"
#include "Entity/entity.h"
#include "Entity/Components/component.h"
#include "Managers/shapemanager.h"
#include "ui_shape.h"
#include "globals.h"

C_ShapeRenderer::C_ShapeRenderer(Entity* owner) : Component(ComponentType::COMPONENT_SHAPE_RENDERER, "Shape renderer", owner)
{

}

void C_ShapeRenderer::Start()
{
    CreateShape(ShapeType::SHAPE_CIRCLE);
}

void C_ShapeRenderer::CleanUp()
{
    ShapeManager::Instance()->DestroyShape(curr_shape);
}

void C_ShapeRenderer::CreateUI()
{
    form = new Ui::Shape();
    ui = new QWidget();
    form->setupUi(ui);

    std::map<ShapeType, std::string> shape_types = ShapeManager::Instance()->GetAllShapeTypes();

    for(std::map<ShapeType, std::string>::iterator it = shape_types.begin(); it != shape_types.end(); ++it)
        form->shapeTypesComboBox->addItem(QString::fromStdString((*it).second), (*it).first);

    connect(form->shapeTypesComboBox, SIGNAL(currentIndexChanged(const QString&)),
            this, SLOT(OnComboBoxShapeChanges(const QString&)));

}

void C_ShapeRenderer::DestroyUI()
{
    delete ui;
}

void C_ShapeRenderer::UpdateUI()
{

}

QWidget *C_ShapeRenderer::GetUI() const
{
    return ui;
}

void C_ShapeRenderer::CreateShape(ShapeType type)
{
    if(curr_shape != nullptr)
    {
        ShapeManager::Instance()->DestroyShape(curr_shape);
    }

    curr_shape = ShapeManager::Instance()->CreateShape(type);
}

void C_ShapeRenderer::OnComboBoxShapeChanges(const QString& new_shape)
{
    ShapeType type = ShapeManager::Instance()->GetShapeTypeByShapeName(new_shape.toStdString());

    CreateShape(type);

    SPOOKYLOG(new_shape.toStdString());
}
