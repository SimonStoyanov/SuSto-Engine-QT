#include "hierarchy.h"
#include "ui_hierarchy.h"
#include "entity.h"

#include "globals.h"

#include <QLabel>

Hierarchy::Hierarchy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hierarchy)
{
    ui->setupUi(this);
}

Hierarchy::~Hierarchy()
{
    delete ui;

    entities.clear();
}

void Hierarchy::on_buttonAddEntity_clicked()
{
    Entity* new_entity = new Entity();

    std::string name = "entity_" + std::to_string(entities.size());

    new_entity->SetName(name);

    SPOOKYLOG(name + + " created succesfully");

    entities.push_back(new_entity);

    /*QLabel* label = new QLabel(QString(name), this);
    ui->scrollArea->setWidget(label);*/
}

void Hierarchy::on_buttonRemoveEntity_clicked()
{

}
