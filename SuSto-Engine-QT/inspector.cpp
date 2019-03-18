#include "globals.h"
#include "Events/event.h"
#include "inspector.h"
#include "mainwindow.h"
#include "hierarchy.h"
#include "hierarchyentity.h"
#include "entity.h"
#include "ui_inspector.h"
#include "Components/c_transform.h"
#include "ui_transform.h"
#include "Managers/eventmanager.h"

#include <functional>
#include <qcombobox>

Inspector::Inspector(MainWindow* mainwindow_, QWidget *parent) :
    QWidget(parent),
    mainwindow(mainwindow_),
    ui(new Ui::Inspector),
    trn(new Ui::Transform)
{
    ui->setupUi(this);

    QWidget *transform = new QWidget;
    trn->setupUi(transform);

    //QWidget *trn = dynamic_cast<QWidget *>(c_trn);
    ui->ComponentsLayout->addWidget(transform);

    EventManager::Instance()->Subscribe(std::bind(&Inspector::onEvent, this, std::placeholders::_1), EventType::EVENT_SELECT_ENTITY_CHANGE);

    connect(ui->entityName, SIGNAL(editingFinished()), mainwindow->GetHierarchy(), SLOT(UpdateSelectedEntity()));
}

Inspector::~Inspector()
{
    delete ui;
    delete trn;
}

void Inspector::SetInspectorView()
{
    ui->entityName->setText(selectedEntity->GetName().c_str());
}

std::string Inspector::GetEntityName()
{
    return ui->entityName->text().toStdString();
}

void Inspector::SetEntityName(std::string new_name)
{
    ui->entityName->setText(new_name.c_str());
}


void Inspector::onEvent(Event* event)
{

}
