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
#include "meshmanager.h"
#include "globals.h"
#include "QTimer"
#include "texturemanager.h"
#include "QObject"

AppManager* AppManager::instance = nullptr;

AppManager::AppManager() : QObject (nullptr)
{

}

void AppManager::Init(QApplication& app)
{

}

void AppManager::Start(QApplication& app)
{
    SPOOKYLOG("Application Manager Start");

    app.installEventFilter(InputManager::Instance());

    JsonManager::Instance()->Start();
    RenderManager::Instance()->Start();
    ShaderManager::Instance()->Start();
    EventManager::Instance()->Start();
    SceneRendererManager::Instance()->Start();
    EntityManager::Instance()->Start();
    CameraManager::Instance()->Start();
    InputManager::Instance()->Start();
    MeshManager::Instance()->Start();
    TextureManager::Instance()->Start();

    workTimer.setInterval(5);
    workTimer.start();

    connect(&workTimer, SIGNAL(timeout()), this, SLOT(Update()));
    dtTimer.start();
}

void AppManager::Update()
{
    dt = (float)-dtTimer.msec() / 1000.0f;

    QTime timer;
    dtTimer = timer;

    EntityManager::Instance()->UpdateAllEntities();
    InputManager::Instance()->Update();
    CameraManager::Instance()->Update();
    RenderManager::Instance()->Update();
}

void AppManager::CleanUp(QApplication& app)
{
    SPOOKYLOG("Application Manager CleanUp");

    workTimer.stop();

    app.removeEventFilter(InputManager::Instance());

    TextureManager::DestroyInstance();
    MeshManager::DestroyInstance();
    InputManager::DestroyInstance();
    CameraManager::DestroyInstance();
    EntityManager::DestroyInstance();
    SceneRendererManager::DestroyInstance();
    EventManager::DestroyInstance();
    ShaderManager::DestroyInstance();
    RenderManager::DestroyInstance();
    JsonManager::DestroyInstance();
}

