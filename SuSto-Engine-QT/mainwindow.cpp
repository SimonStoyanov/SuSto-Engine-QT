#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "globals.h"

#include "hierarchy.h"
#include "rendererwidget.h"

#include <QFile>
#include <QtWidgets>

#include "ads/SectionWidget.h"
#include "ads/DropOverlay.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    hierarchy = new Hierarchy();
    rendering = new RendererWidget();

    // Init Advanced Docking
    advanced_docking_container = new ADS_NS::ContainerWidget();
    setCentralWidget(advanced_docking_container);

    docking_area_hierarchy = ADS_NS::SectionContent::newSectionContent(QString("docking_area_hierarchy"), advanced_docking_container, new QLabel("Hierarchy"), hierarchy);
    docking_area_inspector = ADS_NS::SectionContent::newSectionContent(QString("docking_area_inspector"), advanced_docking_container, new QLabel("Inspector"), hierarchy);
    docking_area_rendering = ADS_NS::SectionContent::newSectionContent(QString("docking_area_rendering"), advanced_docking_container, new QLabel("Scene"), rendering);

    advanced_docking_container->addSectionContent(docking_area_rendering, NULL, ADS_NS::CenterDropArea);
    advanced_docking_container->addSectionContent(docking_area_hierarchy, NULL, ADS_NS::RightDropArea);
    advanced_docking_container->addSectionContent(docking_area_inspector, NULL, ADS_NS::LeftDropArea);

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
    SPOOKYLOG("Exiting the application");
    QApplication::quit();
}

void MainWindow::actionAbout()
{
    QMessageBox::about(this,
        tr("About SuSto Engine"),
        tr("Made by Guillem Sunyer Caldú and Simón Stoyanov Beltrán "
        "for the Advanced Graphics subject."));
}
