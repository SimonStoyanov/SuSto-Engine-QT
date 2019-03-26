#ifndef C_TRANSFORM_H
#define C_TRANSFORM_H

#include "component.h"

namespace Ui {
class Transform;
}

class C_Transform : public Component
{
     Q_OBJECT

public:
    C_Transform(Entity* owner);
    ~C_Transform();

    void CreateUI();
    void DestroyUI();
    void UpdateUI();
    QWidget* GetUI() const;

private:
    QWidget* ui = nullptr;
    Ui::Transform* form = nullptr;
};

#endif // C_TRANSFORM_H
