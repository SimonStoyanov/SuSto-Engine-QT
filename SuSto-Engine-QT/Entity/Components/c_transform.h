#ifndef C_TRANSFORM_H
#define C_TRANSFORM_H

#include "component.h"
#include "3rdParty/MathGeoLib/Math/float2.h"

class C_ShapeRenderer;
class DataAbstraction;

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

    void OnSaveAbstraction(DataAbstraction& abs);
    void OnLoadAbstraction(DataAbstraction& abs);

    void OnComponentAdded(Component* comp);
    void OnComponentRemoved(Component* comp);

    void CreateUI();
    void DestroyUI();
    void UpdateUI();
    QWidget* GetUI() const;

    void SetPos(const float3& set);
    float3 GetPos() const;

    void SetRotationDegrees(const float3& set);
    float3 GetRotationDegrees() const;

    void SetScale(const float3& set);
    float3 GetScale() const;

private slots:
    void OnUIValueChanged(double val);

private:
    QWidget* ui = nullptr;
    Ui::Transform* form = nullptr;

    float3 pos = float3::zero;
    float3 rotation = float3::zero;
    float3 scale = float3::one;

    C_ShapeRenderer* shape_renderer = nullptr;
};

#endif // C_TRANSFORM_H
