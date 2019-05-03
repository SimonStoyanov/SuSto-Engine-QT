#include "appmanager.h"
#include "entitymanager.h"
#include "eventmanager.h"
#include "shapemanager.h"
#include "jsonmanager.h"
#include "rendermanager.h"
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

    JsonManager::Instance()->Start();
    RenderManager::Instance()->Start();
    EventManager::Instance()->Start();
    EntityManager::Instance()->Start();

    workTimer.setInterval(33);
    workTimer.start();

    connect(&workTimer, SIGNAL(timeout()), this, SLOT(Update()));
    dtTimer.start();
}

void AppManager::Update()
{
    dt = dtTimer.msec()/1000;
    dtTimer.start();
    EntityManager::Instance()->UpdateAllEntities();
}

void AppManager::CleanUp()
{
    SPOOKYLOG("Application Manager CleanUp");

    workTimer.stop();

    EntityManager::DestroyInstance();
    JsonManager::DestroyInstance();
    EventManager::DestroyInstance();
    RenderManager::DestroyInstance();
}

