#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>

namespace Ui {
class DrawingWidget;
}

class Shape;

class DrawingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingWidget(QWidget *parent = 0);
    ~DrawingWidget();

    void paintEvent(QPaintEvent* event) override;
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

private:
    Ui::DrawingWidget *ui;

    std::vector<Shape*> shapes;
};

#endif // DRAWINGWIDGET_H
