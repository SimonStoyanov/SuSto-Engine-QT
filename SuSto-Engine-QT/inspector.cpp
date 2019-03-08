#include "globals.h"
#include "inspector.h"
#include "mainwindow.h"
#include "hierarchy.h"
#include "hierarchyentity.h"
#include "entity.h"
#include "ui_inspector.h"

#include <qcombobox>

Inspector::Inspector(MainWindow* mainwindow_, QWidget *parent) :
    QWidget(parent),
    mainwindow(mainwindow_),
    ui(new Ui::Inspector)
{
    ui->setupUi(this);

    connect(ui->entityName, SIGNAL(returnPressed()), mainwindow->GetHierarchy(), SLOT(UpdateSelectedEntity()));
}

Inspector::~Inspector()
{
    delete ui;
}

void Inspector::SetInspectorView()
{
    ui->entityName->setText(selectedEntity->GetName().c_str());
}

std::string Inspector::GetEntityName()
{
    return ui->entityName->text().toStdString();
}
