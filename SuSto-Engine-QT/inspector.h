#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

namespace Ui {
class Inspector;
}

class Entity;
class MainWindow;

class Inspector : public QWidget
{
    Q_OBJECT

public:
    explicit Inspector(MainWindow* mainwindow_, QWidget *parent = 0);
    ~Inspector();

    void SelectEntity(Entity* entity)
    {
        selectedEntity = entity;
    }

private slots:

private:
    MainWindow* mainwindow = nullptr;
    Ui::Inspector *ui = nullptr;
    Entity* selectedEntity = nullptr;
};

#endif // INSPECTOR_H
