#include "rendererwidget.h"

#pragma comment(lib, "OpenGL32.lib")

RendererWidget::RendererWidget(QWidget *parent) : QOpenGLWidget (parent)
{

}

void RendererWidget::initializeGL()
{

}

void RendererWidget::resizeGL()
{

}

void RendererWidget::paintGL()
{
    glClearColor(0.5f, 0.7f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
