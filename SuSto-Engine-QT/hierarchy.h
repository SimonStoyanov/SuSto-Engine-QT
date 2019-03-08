#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <QWidget>

namespace Ui {
class Hierarchy;
}

class Entity;
class HierarchyEntity;
class MainWindow;

class Hierarchy : public QWidget
{
    Q_OBJECT

public:
    explicit Hierarchy(MainWindow* mainwindow_, QWidget *parent = nullptr);
    ~Hierarchy();

    void SetSelected(HierarchyEntity* selected);

private slots:
    void on_buttonAddEntity_clicked();

    void on_buttonRemoveEntity_clicked();

private:
    Ui::Hierarchy *ui;
    MainWindow* mainwindow = nullptr;

    std::list<Entity*> entities;
    HierarchyEntity* selectedEntity = nullptr;

    void CreateEntityInHierarchy(Entity* entity, std::string name);
};

#endif // HIERARCHY_H
