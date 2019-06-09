#include "Entity/Components/c_shape_renderer.h"
#include "Entity/entity.h"
#include "Entity/Components/component.h"
#include "Managers/shapemanager.h"
#include "ui_shape.h"
#include "globals.h"
#include "Entity/Components/c_transform.h"
#include "Managers/jsonmanager.h"

C_ShapeRenderer::C_ShapeRenderer(Entity* owner) : Component(ComponentType::COMPONENT_SHAPE_RENDERER, "Shape renderer", owner, true)
{

}

void C_ShapeRenderer::Start()
{

}

void C_ShapeRenderer::Update()
{

}

void C_ShapeRenderer::CleanUp()
{
    ShapeManager::Instance()->DestroyShape(curr_shape);
}

void C_ShapeRenderer::OnSaveAbstraction(DataAbstraction &abs)
{
    if(curr_shape != nullptr)
    {
        QColor stroke_col = curr_shape->GetStrokeColor();
        QColor fill_col = curr_shape->GetFillColor();

        abs.AddInt("shape_type", curr_shape->GetType());
        abs.AddInt("stroke_type", curr_shape->GetStrockeStyle());
        abs.AddFloat("size", size);
        abs.AddFloat("stroke", stroke);
        abs.AddFloat4("stroke_colour", float4(stroke_col.red(), stroke_col.green(), stroke_col.alpha(), stroke_col.blue()));
        abs.AddFloat4("fill_colour", float4(fill_col.red(), fill_col.green(), fill_col.alpha(), fill_col.blue()));
    }
}

void C_ShapeRenderer::OnLoadAbstraction(DataAbstraction &abs)
{
    ShapeType type = static_cast<ShapeType>(abs.GetInt("shape_type"));
    Qt::PenStyle stroke_style = static_cast<Qt::PenStyle>(abs.GetInt("stroke_type"));

    CreateShape(type);

    if(curr_shape != nullptr)
    {
        size = abs.GetFloat("size");
        stroke = abs.GetFloat("stroke");

        float4 stroke_col = abs.GetFloat4("stroke_colour");
        float4 fill_col = abs.GetFloat4("fill_colour");

        QColor stroke_qcol = QColor::fromRgb(stroke_col.x, stroke_col.y, stroke_col.w, stroke_col.z);
        QColor fill_qcol = QColor::fromRgb(fill_col.x, fill_col.y, fill_col.w, fill_col.z);

        curr_shape->SetStrokeColor(stroke_qcol);
        curr_shape->SetFillColor(fill_qcol);
        curr_shape->SetStrokeStyle(stroke_style);
    }

    UpdateUI();
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

    form->shapeTypesComboBox->setCurrentIndex(0);
    form->strokeStyleComboBox->setCurrentIndex(1);

    CreateShape(ShapeType::SHAPE_CIRCLE);
}

void C_ShapeRenderer::DestroyUI()
{
    delete ui;
}

void C_ShapeRenderer::UpdateUI()
{
    if(curr_shape != nullptr)
    {
        QColor stroke_col = curr_shape->GetStrokeColor();
        QColor fill_col = curr_shape->GetFillColor();

        if(form->shapeTypesComboBox->count() > 0)
        {
            std::string shape_name = ShapeManager::Instance()->GetShapeNameByShapeType(curr_shape->GetType());

            form->shapeTypesComboBox->setCurrentText(QString::fromStdString(shape_name));

            std::string shape_stroke_style = ShapeManager::Instance()->GetStrokeNameByStrokeStyleType(curr_shape->GetStrockeStyle());

            form->strokeStyleComboBox->setCurrentText(QString::fromStdString(shape_stroke_style));

            form->sizeTextInput->setValue(size);
            form->strokeTextInput->setValue(stroke);

            form->strokeR->setValue(stroke_col.red());
            form->strokeG->setValue(stroke_col.green());
            form->strokeB->setValue(stroke_col.blue());
            form->strokeA->setValue(stroke_col.alpha());

            form->fillR->setValue(fill_col.red());
            form->fillG->setValue(fill_col.green());
            form->fillB->setValue(fill_col.blue());
            form->fillA->setValue(fill_col.alpha());
        }
    }
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
