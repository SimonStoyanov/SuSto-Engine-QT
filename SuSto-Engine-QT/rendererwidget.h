#ifndef RENDERERWIDGET_H
#define RENDERERWIDGET_H

#include <QOpenGLWidget>

class RendererWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit RendererWidget(QWidget *parent = nullptr);

    void initializeGL();
    void resizeGL();
    void paintGL();

signals:

public slots:
};

#endif // RENDERERWIDGET_H
