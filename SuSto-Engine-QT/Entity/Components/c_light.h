#ifndef C_LIGHT_H
#define C_LIGHT_H

#include "component.h"

namespace Ui {
class Light;
}

enum LightType
{
    AMBIENT,
    DIRECTIONAL,
    POINT,
};

class C_Light : public Component
{    
public:
    Q_OBJECT

public:
     C_Light(Entity* owner);

     void Start();
     void Update();
     void CleanUp();

     void OnSaveAbstraction(DataAbstraction& abs);
     void OnLoadAbstraction(DataAbstraction& abs);

     void CreateUI();
     void DestroyUI();
     void UpdateUI();
     QWidget *GetUI() const;

private:

private slots:
     void OnComboLightTypeChanges(const QString& new_shape);
     void OnIntensityChanges(double val);


private:
     QWidget* ui = nullptr;
     Ui::Light* form = nullptr;

     LightType type = LightType::POINT;
     float intensity = 0.3f;
};

#endif // C_LIGHT_H