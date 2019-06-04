#include "qapplication.h"
#include "appmanager.h"
#include "entitymanager.h"
#include "eventmanager.h"
#include "shapemanager.h"
#include "jsonmanager.h"
#include "rendermanager.h"
#include "shadermanager.h"
#include "scenerenderermanager.h"
#include "cameramanager.h"
#include "inputmanager.h"
#include "globals.h"
#include "QTimer"
#include "QObject"

AppManager* AppManager::instance = nullptr;

AppManager::AppManager() : QObject (nullptr)
{

}

void AppManager::Init(QApplication& app)
{
    app.installEventFilter(InputManager::Instance());
}

void AppManager::Start()
{
    SPOOKYLOG("Application Manager Start");

    JsonManager::Instance()->Start();
    RenderManager::Instance()->Start();
    ShaderManager::Instance()->Start();
    EventManager::Instance()->Start();
    SceneRendererManager::Instance()->Start();
    EntityManager::Instance()->Start();
    CameraManager::Instance()->Start();
    InputManager::Instance()->Start();

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
    InputManager::Instance()->Update();
}

void AppManager::CleanUp()
{
    SPOOKYLOG("Application Manager CleanUp");

    workTimer.stop();

    InputManager::DestroyInstance();
    CameraManager::DestroyInstance();
    EntityManager::DestroyInstance();
    SceneRendererManager::DestroyInstance();
    EventManager::DestroyInstance();
    ShaderManager::DestroyInstance();
    RenderManager::DestroyInstance();
    JsonManager::DestroyInstance();
}

