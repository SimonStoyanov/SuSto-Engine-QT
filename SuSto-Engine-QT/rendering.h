#ifndef RENDERING_H
#define RENDERING_H

#include <QWidget>

namespace Ui {
class Rendering;
}

class MainWindow;

class Rendering : public QWidget
{
    Q_OBJECT

public:
    explicit Rendering(MainWindow* mainwindow, QWidget *parent = nullptr);
    ~Rendering();

private slots:
    void OnComboRenderingBufferChange(const QString& new_shape);

private:
    MainWindow* mainwindow = nullptr;

    Ui::Rendering *ui;
};

#endif // RENDERING_H
