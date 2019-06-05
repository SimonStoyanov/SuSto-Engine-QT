#include "rendererwidget.h"
#include "Managers/rendermanager.h"
#include "Managers/cameramanager.h"
#include "Managers/scenerenderermanager.h"
#include "globals.h"

#pragma comment(lib, "OpenGL32.lib")

RendererWidget::RendererWidget(MainWindow* _mainwindow_, QWidget *parent)
{
    main_window = _mainwindow_;

    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

void RendererWidget::initializeGL()
{
    initializeOpenGLFunctions();

    RenderManager::Instance()->SetGL(this);
}

void RendererWidget::resizeGL(int w, int h)
{
    glClearColor(1.5f, 0.7f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SceneRendererManager::Instance()->RenderOnCamera(w, h);
}

void RendererWidget::paintGL()
{
    glClearColor(1.5f, 0.7f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SceneRendererManager::Instance()->RenderOnCamera();
}

void RendererWidget::mouseMoveEvent(QMouseEvent *event)
{

}

