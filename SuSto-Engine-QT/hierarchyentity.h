#ifndef HIERARCHYENTITY_H
#define HIERARCHYENTITY_H

#include <QWidget>

namespace Ui {
class HierarchyEntity;
}

class Entity;

class HierarchyEntity : public QWidget
{
    Q_OBJECT

public:
    explicit HierarchyEntity(Entity* entity, QWidget *parent = 0);
    ~HierarchyEntity();

    void SetName(std::string name);

private:
    Ui::HierarchyEntity *ui;
    Entity* parentEntity = nullptr;
};

#endif // HIERARCHYENTITY_H
