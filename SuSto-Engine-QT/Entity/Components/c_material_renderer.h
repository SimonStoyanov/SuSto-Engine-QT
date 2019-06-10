#ifndef C_MATERIAL_RENDERER_H
#define C_MATERIAL_RENDERER_H

#include "component.h"

namespace Ui {
class MaterialRenderer;
}

class Event;
class Texture;

class C_MaterialRenderer : public Component
{
public:    
    Q_OBJECT

public:
     C_MaterialRenderer(Entity* owner);

     void Start();
     void Update();
     void CleanUp();

     void OnSaveAbstraction(DataAbstraction& abs);
     void OnLoadAbstraction(DataAbstraction& abs);

     void CreateUI();
     void DestroyUI();
     void UpdateUI();
     QWidget *GetUI() const;

     void SetDiffuseTexture(Texture* tex);
     void SetNormalTexture(Texture* tex);
     void SetHeightTexture(Texture* tex);

     Texture* GetDiffuseTexture() const;
     Texture* GetNormalTexture() const;
     Texture* GetHeightTexture() const;

private:
     void OnEvent(Event* ev);

     void UpdateTexturesComboBoxes();

private slots:
   void OnSelectedDiffuseChange(const QString& new_shape);
   void OnSelectedNormalChange(const QString& new_shape);
   void OnSelectedHeightChange(const QString& new_shape);

private:
     QWidget* ui = nullptr;
     Ui::MaterialRenderer* form = nullptr;

     Texture* diffuse_texture = nullptr;
     Texture* normal_texture = nullptr;
     Texture* height_texture = nullptr;
};

#endif // C_MATERIAL_RENDERER_H
