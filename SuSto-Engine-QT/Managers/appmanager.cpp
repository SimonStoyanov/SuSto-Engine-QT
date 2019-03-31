#include "appmanager.h"
#include "entitymanager.h"
#include "eventmanager.h"
#include "shapemanager.h"
#include "jsonmanager.h"
#include "globals.h"
#include "QTimer"
#include "QObject"

AppManager* AppManager::instance = nullptr;

AppManager::AppManager() : QObject (nullptr)
{

}

void AppManager::Init()
{

}

void AppManager::Start()
{
    SPOOKYLOG("Application Manager Start");

    workTimer.setInterval(33);
    workTimer.start();

    connect(&workTimer, SIGNAL(timeout()), this, SLOT(Update()));
}

void AppManager::Update()
{
    EntityManager::Instance()->UpdateAllEntities();
    ShapeManager::Instance()->RepaintDrawingWidget();
}

void AppManager::CleanUp()
{
    SPOOKYLOG("Application Manager CleanUp");

    workTimer.stop();

    EntityManager::DestroyInstance();
    ShapeManager::DestroyInstance();
    JsonManager::DestroyInstance();
    EventManager::DestroyInstance();
}

