#ifndef HIERARCHYENTITY_H
#define HIERARCHYENTITY_H

#include <QWidget>

namespace Ui {
class HierarchyEntity;
}

class Entity;
class Hierarchy;

class HierarchyEntity : public QWidget
{
    Q_OBJECT

public:
    explicit HierarchyEntity(Entity* entity, Hierarchy* hierarchy_, QWidget *parent = 0);
    ~HierarchyEntity();

    Entity* GetParent(){
        return parentEntity;
    }

    void SetName(std::string name);

private slots:
    void on_entityName_clicked();

private:
    Ui::HierarchyEntity *ui;
    Entity* parentEntity = nullptr;
    Hierarchy* hierarchy = nullptr;
};

#endif // HIERARCHYENTITY_H
