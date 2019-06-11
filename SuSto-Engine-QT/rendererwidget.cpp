#include "rendererwidget.h"
#include "Managers/rendermanager.h"
#include "Managers/cameramanager.h"
#include "Managers/scenerenderermanager.h"
#include "globals.h"
#include <QOpenGLFramebufferObject>

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
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SceneRendererManager::Instance()->ResizeRenderTarget(w, h);

    SceneRendererManager::Instance()->RenderOnCamera(w, h);

    QOpenGLFramebufferObject::bindDefault();

    SceneRendererManager::Instance()->RenderRenderTarget();
}

void RendererWidget::paintGL()
{
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SceneRendererManager::Instance()->RenderOnCamera();

    QOpenGLFramebufferObject::bindDefault();

    SceneRendererManager::Instance()->RenderRenderTarget();
}

void RendererWidget::mouseMoveEvent(QMouseEvent *event)
{

}

