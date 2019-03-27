#ifndef C_SHAPERENDERER_H
#define C_SHAPERENDERER_H

#include "component.h"

#include "Shapes/shape.h"

namespace Ui {
class Shape;
}

class C_ShapeRenderer : public Component
{
     Q_OBJECT

public:
    C_ShapeRenderer(Entity* owner);

    void Start();
    void Update();
    void CleanUp();

    void CreateUI();
    void DestroyUI();
    void UpdateUI();
    QWidget* GetUI() const;

    Shape* GetShape() const;

    void SetSize(float size);
    void SetStroke(float stroke);

private:
    void CreateShape(ShapeType type);

private slots:
    void OnComboBoxShapeChanges(const QString& new_shape);
    void OnComboBoxStrokeStyleChanges(const QString& new_shape);
    void OnUIValueChanged(double val);
    void OnUIColoursChanged(int val);

private:
    QWidget* ui = nullptr;
    Ui::Shape* form = nullptr;

    Shape* curr_shape = nullptr;

    float size = 1;
    float stroke = 1;
};

#endif // C_SHAPERENDERER_H
