#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hierarchyentity.h"
#include "ui_inspector.h"

#include "globals.h"

#include "hierarchy.h"
#include "inspector.h"
#include "rendererwidget.h"

#include <QFile>
#include <QtWidgets>

#include "ads/SectionWidget.h"
#include "ads/DropOverlay.h"

#include "Managers/entitymanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    hierarchy = new Hierarchy(this);
    inspector = new Inspector(this);
    rendering = new RendererWidget();

    // Init Advanced Docking
    advanced_docking_container = new ADS_NS::ContainerWidget();
    setCentralWidget(advanced_docking_container);

    docking_area_hierarchy = ADS_NS::SectionContent::newSectionContent(QString("docking_area_hierarchy"), advanced_docking_container, new QLabel("Hierarchy"), hierarchy);
    docking_area_inspector = ADS_NS::SectionContent::newSectionContent(QString("docking_area_inspector"), advanced_docking_container, new QLabel("Inspector"), inspector);
    docking_area_rendering = ADS_NS::SectionContent::newSectionContent(QString("docking_area_rendering"), advanced_docking_container, new QLabel("Scene"), rendering);

    advanced_docking_container->addSectionContent(docking_area_rendering, NULL, ADS_NS::CenterDropArea);
    advanced_docking_container->addSectionContent(docking_area_hierarchy, NULL, ADS_NS::LeftDropArea);
    advanced_docking_container->addSectionContent(docking_area_inspector, NULL, ADS_NS::RightDropArea);

    // TOOLBAR FILE
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(actionCreateFile()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(actionExit()));

    // TOOLBAR EDIT
    connect(ui->actionCopy, SIGNAL(triggered()), hierarchy, SLOT(CopyEntity()));
    connect(ui->actionPaste, SIGNAL(triggered()), hierarchy, SLOT(PasteEntity()));
    connect(ui->actionDelete, SIGNAL(triggered()), hierarchy, SLOT(on_buttonRemoveEntity_clicked()));

    // TOOLBAR HELP
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(actionAbout()));

    // INSPECTOR
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
void MainWindow::on_actionWindowsRenderer_triggered()
{
    if (ui->actionWindowsRenderer->isChecked())
        advanced_docking_container->showSectionContent(docking_area_rendering);
    else
        advanced_docking_container->hideSectionContent(docking_area_rendering);
}

void MainWindow::on_actionWindowsInspector_triggered()
{
    if (ui->actionWindowsInspector->isChecked())
        advanced_docking_container->showSectionContent(docking_area_inspector);
    else
        advanced_docking_container->hideSectionContent(docking_area_inspector);
}

void MainWindow::on_actionWindowsHierarchy_triggered()
{
    if (ui->actionWindowsHierarchy->isChecked())
        advanced_docking_container->showSectionContent(docking_area_hierarchy);
    else
        advanced_docking_container->hideSectionContent(docking_area_hierarchy);
}
