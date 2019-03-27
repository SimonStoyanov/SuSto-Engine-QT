#include "Entity/Components/c_shape_renderer.h"
#include "Entity/entity.h"
#include "Entity/Components/component.h"
#include "Managers/shapemanager.h"
#include "ui_shape.h"
#include "globals.h"
#include "Entity/Components/c_transform.h"

C_ShapeRenderer::C_ShapeRenderer(Entity* owner) : Component(ComponentType::COMPONENT_SHAPE_RENDERER, "Shape renderer", owner, true)
{

}

void C_ShapeRenderer::Start()
{

}

void C_ShapeRenderer::Update()
{
    if(curr_shape != nullptr)
    {
        curr_shape->SetPos(GetOwner()->GetTransform()->GetPos());

        float2 new_size = GetOwner()->GetTransform()->GetScale() * size;
        curr_shape->SetSize(new_size);

        curr_shape->SetStrokeThickness(stroke);
    }
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

    connect(form->sizeTextInput, SIGNAL(valueChanged(double)), this, SLOT(OnUIValueChanged(double)));
    connect(form->strokeTextInput, SIGNAL(valueChanged(double)), this, SLOT(OnUIValueChanged(double)));

    form->sizeTextInput->setValue(80);
    form->strokeTextInput->setValue(10);

    connect(form->strokeR, SIGNAL(valueChanged(int)), this, SLOT(OnUIColoursChanged(int)));
    connect(form->strokeG, SIGNAL(valueChanged(int)), this, SLOT(OnUIColoursChanged(int)));
    connect(form->strokeB, SIGNAL(valueChanged(int)), this, SLOT(OnUIColoursChanged(int)));
    connect(form->strokeA, SIGNAL(valueChanged(int)), this, SLOT(OnUIColoursChanged(int)));

    connect(form->fillR, SIGNAL(valueChanged(int)), this, SLOT(OnUIColoursChanged(int)));
    connect(form->fillG, SIGNAL(valueChanged(int)), this, SLOT(OnUIColoursChanged(int)));
    connect(form->fillB, SIGNAL(valueChanged(int)), this, SLOT(OnUIColoursChanged(int)));
    connect(form->fillA, SIGNAL(valueChanged(int)), this, SLOT(OnUIColoursChanged(int)));

    form->strokeA->setValue(255);
    form->fillA->setValue(255);
    form->fillR->setValue(255);

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

Shape *C_ShapeRenderer::GetShape() const
{
    return curr_shape;
}

void C_ShapeRenderer::SetSize(float set)
{
    size = set;
}

void C_ShapeRenderer::SetStroke(float set)
{
    stroke = set;
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
        OnUIValueChanged(0);
        OnUIColoursChanged(0);
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

void C_ShapeRenderer::OnUIValueChanged(double val)
{
    if(curr_shape != nullptr)
    {
        size = form->sizeTextInput->value();
        stroke = form->strokeTextInput->value();
    }
}

void C_ShapeRenderer::OnUIColoursChanged(int val)
{
    if(curr_shape != nullptr)
    {
        QColor fill;
        fill.setRgb(form->fillR->value(), form->fillG->value(), form->fillB->value(), form->fillA->value());
        curr_shape->SetFillColor(fill);

        QColor stroke;
        stroke.setRgb(form->strokeR->value(), form->strokeG->value(), form->strokeB->value(), form->strokeA->value());
        curr_shape->SetStrokeColor(stroke);

        SPOOKYLOG(std::to_string( curr_shape->GetFillColor().red()));
    }
}
