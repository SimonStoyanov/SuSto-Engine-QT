#ifndef C_MESH_RENDERER_H
#define C_MESH_RENDERER_H

#include "component.h"
#include "Renderers/mesh.h"

class Event;

namespace Ui {
class MeshRenderer;
}

class C_MeshRenderer : public Component
{
public:
    C_MeshRenderer();

    Q_OBJECT

public:
   C_MeshRenderer(Entity* owner);

   void Start();
   void Update();
   void CleanUp();

   void OnSaveAbstraction(DataAbstraction& abs);
   void OnLoadAbstraction(DataAbstraction& abs);

   void CreateUI();
   void DestroyUI();
   void UpdateUI();
   QWidget* GetUI() const;

   void SetMesh(Mesh* mesh);
   Mesh *GetMesh() const;

private:
   void OnEvent(Event* ev);

   void UpdateMeshComboBox();

private slots:
   void OnSelectedMeshChanges(const QString& new_shape);

private:
   QWidget* ui = nullptr;
   Ui::MeshRenderer* form = nullptr;

   Mesh* mesh = nullptr;

};


#endif // C_MESH_RENDERER_H
