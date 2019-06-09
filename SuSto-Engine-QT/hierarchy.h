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

public slots:
    void UpdateUI();

    void UpdateEntitiesUI();

    void NewScene();
    void SaveScene();
    void LoadScene();

    void LoadModel();
    void LoadMesh();
    void LoadTexture();

private slots:
    void on_buttonAddEntity_clicked();
    void on_buttonRemoveEntity_clicked();

    void DuplicateEntity();

private:
    Ui::Hierarchy *ui;
    MainWindow* mainwindow = nullptr;

    std::vector<HierarchyEntity*> h_entities;
};

#endif // HIERARCHY_H
