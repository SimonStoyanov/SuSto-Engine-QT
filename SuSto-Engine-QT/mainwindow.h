#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Hierarchy;

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

private:
    Ui::MainWindow *ui;
    Hierarchy *hierarchy;
};

#endif // MAINWINDOW_H
