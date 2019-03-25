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
#include "Managers/entitymanager.h"
#include "Events/event.h"
#include "Events/selectentitychange.h"

#include <functional>
#include <QComboBox>

Inspector::Inspector(MainWindow* mainwindow_, QWidget *parent) :
    QWidget(parent),
    mainwindow(mainwindow_),
    ui(new Ui::Inspector),
    trn(new Ui::Transform)
{
    ui->setupUi(this);

    EventManager::Instance()->Subscribe(std::bind(&Inspector::OnEvent, this, std::placeholders::_1), EventType::EVENT_SELECT_ENTITY_CHANGE);

    QWidget *transform = new QWidget;
    trn->setupUi(transform);

    ui->ComponentsLayout->addWidget(transform);

    connect(ui->entityName, SIGNAL(editingFinished()), this, SLOT(SetEntityDataFromUI()));
    connect(ui->entityName, SIGNAL(textChanged(QString)), this, SLOT(EntityNameChanged(QString)));
}

Inspector::~Inspector()
{
    delete ui;
    delete trn;
}

void Inspector::UpdateUI()
{
    Entity* selected_entity = EntityManager::Instance()->GetSelectedEntity();

    if(selected_entity != nullptr)
    {
        ui->entityName->setText(selected_entity->GetName().c_str());
    }
    else
    {
        ui->entityName->setText("");
    }

    mainwindow->GetHierarchy()->UpdateUI();

    SPOOKYLOG("updating inspector ui");
}

void Inspector::EntityNameChanged(const QString& str)
{
    Entity* selected_entity = EntityManager::Instance()->GetSelectedEntity();

    if(selected_entity != nullptr)
    {
        selected_entity->SetName(str.toStdString());
    }

    UpdateUI();
}

void Inspector::SetEntityDataFromUI()
{    
    Entity* selected_entity = EntityManager::Instance()->GetSelectedEntity();

    if(selected_entity != nullptr)
    {
        selected_entity->SetName(ui->entityName->text().toStdString());
    }

    UpdateUI();
}


void Inspector::OnEvent(Event* event)
{
    switch(event->GetType())
    {
    case EventType::EVENT_SELECT_ENTITY_CHANGE:
    {
        SPOOKYLOG("event");
        UpdateUI();
        break;
    }
    }
}
