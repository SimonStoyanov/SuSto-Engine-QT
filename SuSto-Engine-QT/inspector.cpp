#include "inspector.h"
#include "mainwindow.h"
#include "ui_inspector.h"

Inspector::Inspector(QWidget *parent, MainWindow* mainwindow_) :
    QWidget(parent),
    mainwindow(mainwindow_),
    ui(new Ui::Inspector)
{
    ui->setupUi(this);
}

Inspector::~Inspector()
{
    delete ui;
}
