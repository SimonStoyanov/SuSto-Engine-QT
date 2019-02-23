#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextStream>

#include <QFile>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // FILE
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(actionCreateFile()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(actionExit()));

    // EDIT

    // HELP
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(actionAbout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actionCreateFile()
{
    QFile file("new_file");
    file.open(QFile::ReadOnly | QFile::Text);
}

void MainWindow::actionExit()
{
    QTextStream out(stdout);
    out << "Exiting the application" << endl;
    QApplication::quit();
}

void MainWindow::actionAbout()
{
    QMessageBox::about(this,
        tr("About SuSto Engine"),
        tr("Made by Guillem Sunyer Caldú and Simón Stoyanov Beltrán "
        "for the Advanced Graphics subject."));
}
