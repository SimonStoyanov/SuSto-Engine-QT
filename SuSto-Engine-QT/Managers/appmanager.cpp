#include "appmanager.h"
#include "entitymanager.h"
#include "eventmanager.h"
#include "globals.h"

AppManager* AppManager::instance = nullptr;

AppManager::AppManager()
{

}

void AppManager::Init()
{

}

void AppManager::Start()
{
    SPOOKYLOG("Application Manager Start");
}

void AppManager::CleanUp()
{
    SPOOKYLOG("Application Manager CleanUp");

    EntityManager::DestroyInstance();
    EventManager::DestroyInstance();
}
