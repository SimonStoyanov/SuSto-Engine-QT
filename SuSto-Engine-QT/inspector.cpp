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
#include "UI/GeneralWidgets/floatingcontext.h"
#include "UI/uiutils.h"

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
    connect(ui->addComponentButton, SIGNAL(pressed()), this, SLOT(AddComponentButton()));
}

Inspector::~Inspector()
{
    delete ui;
}

void Inspector::UpdateUI()
{
    if(update_ui)
    {
        update_ui = false;

        Entity* selected_entity = EntityManager::Instance()->GetSelectedEntity();

        UIUtils::RemoveWidgetsFromLayout(ui->componentsLayout);

        if(selected_entity != nullptr)
        {
            ui->entityName->setText(selected_entity->GetName().c_str());

            std::vector<Component*> components = selected_entity->GetComponents();

            int counter = 0;
            for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it, ++counter)
            {
                QHBoxLayout* h_layout = new QHBoxLayout();

                QWidget *lineB = new QWidget;
                lineB->setFixedHeight(2);
                lineB->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
                lineB->setStyleSheet(QString("background-color: #c0c0c0;"));

                QLabel* label = new QLabel();
                label->setText(QString::fromStdString((*it)->GetName()));
                h_layout->addWidget(label);

                if((*it)->GetCanDelete())
                {
                    //QPushButton* delete_button = new QPushButton();
                    //delete_button->setText("X");
                    //h_layout->addWidget(delete_button);

                    //connect(delete_button, &QPushButton::clicked, [this, delete_button]()
                    //{RemoveComponentButton((*it));});
                }

                QWidget* widget = (*it)->GetUI();

                ui->componentsLayout->addWidget(lineB);
                ui->componentsLayout->addLayout(h_layout);
                ui->componentsLayout->addWidget(widget);
            }
        }
        else
        {
            ui->entityName->setText("");
        }

        mainwindow->GetHierarchy()->UpdateUI();

        update_ui = true;
    }
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

void Inspector::AddComponentButton()
{
    FloatingContext* f_context = new FloatingContext(nullptr);
    f_context->setWindowTitle("Add component");
    f_context->SetDescription("Select a new component to add.");

    std::vector<std::string> content;

    std::map<ComponentType, std::string> component_types = EntityManager::Instance()->GetAllComponentTypes();

    for(std::map<ComponentType, std::string>::iterator it = component_types.begin(); it != component_types.end(); ++it)
        content.push_back((*it).second);

    f_context->SetContent(content);

    f_context->show();
    connect(f_context, SIGNAL(dialogClosed(std::string)),this, SLOT(AddComponentSelected(std::string)));
}

void Inspector::RemoveComponentButton(Component *comp)
{

}

void Inspector::AddComponentSelected(const std::string &component)
{
    if(component.compare("") != 0)
    {
        ComponentType type = EntityManager::Instance()->GetComponentTypeByComponentName(component);

        Entity* selected_entity = EntityManager::Instance()->GetSelectedEntity();

        if(selected_entity != nullptr)
        {
            selected_entity->AddComponent(type);
        }
    }

    UpdateUI();
}

void Inspector::OnEvent(Event* event)
{
    switch(event->GetType())
    {
    case EventType::EVENT_SELECT_ENTITY_CHANGE:
    {
        UpdateUI();
        break;
    }
    }
}

