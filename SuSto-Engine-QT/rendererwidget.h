#ifndef RENDERERWIDGET_H
#define RENDERERWIDGET_H

#include <QOpenGLWidget>

class MainWindow;

class RendererWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit RendererWidget(MainWindow* mainwindow_, QWidget *parent = nullptr);

    void initializeGL();
    void resizeGL();
    void paintGL();

signals:

public slots:

private:
    MainWindow* main_window = nullptr;
};

#endif // RENDERERWIDGET_H
