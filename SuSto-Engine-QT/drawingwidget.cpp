#include "drawingwidget.h"
#include "ui_drawingwidget.h"
#include "globals.h"
#include "Managers/shapemanager.h"

DrawingWidget::DrawingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawingWidget)
{
    ui->setupUi(this);
}

DrawingWidget::~DrawingWidget()
{
    delete ui;
}

void DrawingWidget::paintEvent(QPaintEvent *event)
{    
    setAutoFillBackground(true);

    std::vector<Shape*> shapes = ShapeManager::Instance()->GetShapes();

    QPainter painter(this);

    QColor blue_color = QColor::fromRgb(127, 190, 210);

    QBrush brush;
    QPen pen;

    brush.setColor(blue_color);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    pen.setStyle(Qt::PenStyle::NoPen);
    painter.setBrush(brush);
    painter.setPen(pen);

    painter.drawRect(rect());

    for(std::vector<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it)
    {
        (*it)->Redraw(painter);
    }
}

QSize DrawingWidget::sizeHint() const
{
    return QSize(250, 250);
}

QSize DrawingWidget::minimumSizeHint() const
{
    return QSize(250, 250);
}
