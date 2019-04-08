#include "rendererwidget.h"

#pragma comment(lib, "OpenGL32.lib")

RendererWidget::RendererWidget(MainWindow* _mainwindow_, QWidget *parent)
{
    main_window = _mainwindow_;
}

void RendererWidget::initializeGL()
{

}

void RendererWidget::resizeGL()
{

}

void RendererWidget::paintGL()
{
    glClearColor(1.5f, 0.7f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RendererWidget::keyPressEvent(QKeyEvent *event)
{

}

void RendererWidget::keyReleaseEvent(QKeyEvent *event)
{

}

void RendererWidget::mousePressEvent(QKeyEvent *event)
{

}

void RendererWidget::mouseReleaseEvent(QKeyEvent *event)
{

}

void RendererWidget::mouseDoubleClickEvent(QKeyEvent *event)
{

}
