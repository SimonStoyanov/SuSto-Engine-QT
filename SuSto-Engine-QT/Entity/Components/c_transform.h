#ifndef C_TRANSFORM_H
#define C_TRANSFORM_H

#include "component.h"
#include "3rdParty/MathGeoLib/Math/float2.h"

class C_ShapeRenderer;

namespace Ui {
class Transform;
}

class C_Transform : public Component
{
     Q_OBJECT

public:
    C_Transform(Entity* owner);
    ~C_Transform();

    void Start();
    void CleanUp();

    void OnComponentAdded(Component* comp);
    void OnComponentRemoved(Component* comp);

    void CreateUI();
    void DestroyUI();
    void UpdateUI();
    QWidget* GetUI() const;

    void SetPos(const float2& set);
    float2 GetPos() const;

    void SetScale(const float2& set);
    float2 GetScale() const;

private slots:
    void OnUIValueChanged(double val);

private:
    QWidget* ui = nullptr;
    Ui::Transform* form = nullptr;

    float2 pos = float2::zero;
    float2 scale = float2::one;

    C_ShapeRenderer* shape_renderer = nullptr;
};

#endif // C_TRANSFORM_H
