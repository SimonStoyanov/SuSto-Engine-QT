#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <QWidget>

namespace Ui {
class Hierarchy;
}

class Entity;

class Hierarchy : public QWidget
{
    Q_OBJECT

public:
    explicit Hierarchy(QWidget *parent = nullptr);
    ~Hierarchy();

private slots:
    void on_buttonAddEntity_clicked();

    void on_buttonRemoveEntity_clicked();

private:
    Ui::Hierarchy *ui;
    std::list<Entity*> entities;
};

#endif // HIERARCHY_H
