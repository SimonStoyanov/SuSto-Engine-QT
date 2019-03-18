#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

namespace Ui {
class Inspector;
class Transform;
}

class Entity;
class MainWindow;
class Event;

class Inspector : public QWidget
{
    Q_OBJECT

public:
    explicit Inspector(MainWindow* mainwindow_, QWidget *parent = 0);
    ~Inspector();

    void SelectEntity(Entity* entity)
    {
        selectedEntity = entity;
        SetInspectorView();
    }

    void SetInspectorView();


public:
    std::string GetEntityName();  
    void SetEntityName(std::string new_name);
    void onEvent(Event *event);
private:
    MainWindow* mainwindow = nullptr;
    Ui::Inspector *ui = nullptr;
    Ui::Transform *trn = nullptr;
    Entity* selectedEntity = nullptr;
};

#endif // INSPECTOR_H
