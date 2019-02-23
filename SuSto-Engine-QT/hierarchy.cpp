#include "hierarchy.h"
#include "ui_hierarchy.h"

Hierarchy::Hierarchy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hierarchy)
{
    ui->setupUi(this);
}

Hierarchy::~Hierarchy()
{
    delete ui;
}

void Hierarchy::on_buttonAddEntity_clicked()
{

}

void Hierarchy::on_buttonRemoveEntity_clicked()
{

}
