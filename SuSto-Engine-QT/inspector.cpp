#include "globals.h"
#include "inspector.h"
#include "mainwindow.h"
#include "hierarchy.h"
#include "entity.h"
#include "ui_inspector.h"

Inspector::Inspector(MainWindow* mainwindow_, QWidget *parent) :
    QWidget(parent),
    mainwindow(mainwindow_),
    ui(new Ui::Inspector)
{
    ui->setupUi(this);

    //connect(ui->entityName, SIGNAL(returnPressed()), mainwindow_->hierarchy->e )
}

Inspector::~Inspector()
{
    delete ui;
}

void Inspector::SetInspectorView()
{
    ui->entityName->setText(selectedEntity->GetName().c_str());
    SPOOKYLOG(selectedEntity->GetName());
}
