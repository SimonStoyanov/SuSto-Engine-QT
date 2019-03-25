#include "globals.h"
#include "Events/event.h"
#include "inspector.h"
#include "mainwindow.h"
#include "hierarchy.h"
#include "hierarchyentity.h"
#include "Entity/entity.h"
#include "ui_inspector.h"
#include "ui_transform.h"
#include "Managers/eventmanager.h"
#include "Managers/entitymanager.h"
#include "Events/event.h"
#include "Events/selectentitychange.h"
#include "Entity/Components/component.h"

#include <functional>
#include <QComboBox>

Inspector::Inspector(MainWindow* mainwindow_, QWidget *parent) :
    QWidget(parent),
    mainwindow(mainwindow_),
    ui(new Ui::Inspector)
{
    ui->setupUi(this);

    EventManager::Instance()->Subscribe(std::bind(&Inspector::OnEvent, this, std::placeholders::_1), EventType::EVENT_SELECT_ENTITY_CHANGE);

    connect(ui->entityName, SIGNAL(textChanged(QString)), this, SLOT(EntityNameChanged(QString)));
}

Inspector::~Inspector()
{
    delete ui;
}

void Inspector::UpdateUI()
{
    Entity* selected_entity = EntityManager::Instance()->GetSelectedEntity();

    RemoveAllComponents();

    if(selected_entity != nullptr)
    {
        ui->entityName->setText(selected_entity->GetName().c_str());

        std::vector<Component*> components = selected_entity->GetComponents();

        for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
        {
            QWidget* widget = (*it)->GetUI();

            components_widgets.push_back(widget);

            ui->ComponentsLayout->addWidget(widget);
        }
    }
    else
    {
        ui->entityName->setText("");
    }

    mainwindow->GetHierarchy()->UpdateUI();
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

void Inspector::RemoveAllComponents()
{
    for(std::vector<QWidget*>::iterator it = components_widgets.begin(); it != components_widgets.end(); ++it)
    {
        (*it)->setParent(nullptr);
        ui->ComponentsLayout->removeWidget((*it));
    }

    components_widgets.clear();
}
