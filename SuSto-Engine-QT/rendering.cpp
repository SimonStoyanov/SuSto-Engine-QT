#include "rendering.h"
#include "ui_rendering.h"
#include "mainwindow.h"
#include "Managers/scenerenderermanager.h"
#include <qwidget.h>
#include "globals.h"

Rendering::Rendering(MainWindow* mainwindow_, QWidget *parent) :
    QWidget(parent),
    mainwindow(mainwindow_),
    ui(new Ui::Rendering)
{
    ui->setupUi(this);

    ui->ComboRenderingBuffer->addItem("All", RenderingBuffer::BUFFER_ALL);
    ui->ComboRenderingBuffer->addItem("Positions", RenderingBuffer::BUFFER_POSITION);
    ui->ComboRenderingBuffer->addItem("Normals", RenderingBuffer::BUFFER_NORMALS);
    ui->ComboRenderingBuffer->addItem("Albedo", RenderingBuffer::BUFFER_ALBEDO);
    ui->ComboRenderingBuffer->addItem("Depth", RenderingBuffer::BUFFER_DEPTH);

    ui->ComboRenderingBuffer->setCurrentIndex(0);

    connect(ui->ComboRenderingBuffer, SIGNAL(currentIndexChanged(const QString&)),
            this, SLOT(OnComboRenderingBufferChange(const QString&)));

    ui->AmbientLight->setValue(0.4f);
    connect(ui->AmbientLight, SIGNAL(valueChanged(double)), this, SLOT(OnAmbientLightChanges(double)));
}

Rendering::~Rendering()
{
    delete ui;
}

void Rendering::OnComboRenderingBufferChange(const QString &new_shape)
{
    int data = ui->ComboRenderingBuffer->itemData(ui->ComboRenderingBuffer->currentIndex()).toInt();

    RenderingBuffer type = (RenderingBuffer)data;

    SceneRendererManager::Instance()->SetRenderingBuffer(type);
}

void Rendering::OnAmbientLightChanges(double val)
{
    SceneRendererManager::Instance()->SetAmbientLight(val);
}
