#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ads/API.h"
#include "ads/ContainerWidget.h"
#include "ads/SectionContent.h"

namespace Ui {
class MainWindow;
}

class Hierarchy;
class RendererWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    // FILE
    void actionCreateFile();
    void actionExit();
    // EDIT

    // HELP
    void actionAbout();

    void on_actionWindowsRenderer_triggered();

    void on_actionWindowsInspector_triggered();

    void on_actionWindowsHierarchy_triggered();

private:
    Ui::MainWindow* ui;
    Hierarchy* hierarchy;
    RendererWidget* rendering;

    // The main container for dockings.
    ADS_NS::ContainerWidget* advanced_docking_container = nullptr;
    ADS_NS::SectionContent::RefPtr docking_area_hierarchy = nullptr;
    ADS_NS::SectionContent::RefPtr docking_area_inspector = nullptr;
    ADS_NS::SectionContent::RefPtr docking_area_rendering = nullptr;
};

#endif // MAINWINDOW_H
