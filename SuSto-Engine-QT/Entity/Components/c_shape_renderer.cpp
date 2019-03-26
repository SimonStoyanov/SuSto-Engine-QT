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

    std::map<Qt::PenStyle, std::string> stroke_styles = ShapeManager::Instance()->GetAllStrokeStyleTypes();

    for(std::map<Qt::PenStyle, std::string>::iterator it = stroke_styles.begin(); it != stroke_styles.end(); ++it)
        form->strokeStyleComboBox->addItem(QString::fromStdString((*it).second));

    connect(form->strokeStyleComboBox, SIGNAL(currentIndexChanged(const QString&)),
            this, SLOT(OnComboBoxStrokeStyleChanges(const QString&)));

    form->strokeStyleComboBox->setCurrentIndex(1);

     CreateShape(ShapeType::SHAPE_CIRCLE);
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

    if(curr_shape != nullptr)
    {
        OnComboBoxStrokeStyleChanges("");
    }
}

void C_ShapeRenderer::OnComboBoxShapeChanges(const QString& new_shape)
{
    if(form->shapeTypesComboBox->count() > 0)
    {
        QString curr_val = form->shapeTypesComboBox->itemText(form->shapeTypesComboBox->currentIndex());

        if(form->shapeTypesComboBox->currentIndex() < 0)
            curr_val = form->shapeTypesComboBox->itemText(0);

        std::string new_name = curr_val.toStdString();

        ShapeType type = ShapeManager::Instance()->GetShapeTypeByShapeName(new_name);

        CreateShape(type);
    }
}

void C_ShapeRenderer::OnComboBoxStrokeStyleChanges(const QString &name)
{
    if(curr_shape != nullptr)
    {
        if(form->strokeStyleComboBox->count() > 0)
        {
            QString curr_val = form->strokeStyleComboBox->itemText(form->strokeStyleComboBox->currentIndex());

            if(form->strokeStyleComboBox->currentIndex() < 0)
                curr_val = form->strokeStyleComboBox->itemText(0);

            std::string new_name = curr_val.toStdString();

            Qt::PenStyle stroke_style = ShapeManager::Instance()->GetStrokeStyleTypeByStrokeStyleName(new_name);

            curr_shape->SetStrokeStyle(stroke_style);
        }
    }
}
