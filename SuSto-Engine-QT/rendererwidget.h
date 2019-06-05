#ifndef RENDERERWIDGET_H
#define RENDERERWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

class MainWindow;

class RendererWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit RendererWidget(MainWindow* mainwindow_, QWidget *parent = nullptr);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mouseMoveEvent(QMouseEvent *event);

private:
    MainWindow* main_window = nullptr;

};

#endif // RENDERERWIDGET_H
