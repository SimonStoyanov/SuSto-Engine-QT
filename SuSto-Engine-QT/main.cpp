#include "mainwindow.h"
#include <QApplication>
#include "3rdParty/DarkStyle/framelesswindow/framelesswindow.h"
#include "3rdParty/DarkStyle/DarkStyle.h"
#include "Managers/appmanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle(new DarkStyle);

    AppManager::Instance()->Init();

    FramelessWindow framelessWindow;
    framelessWindow.setWindowIcon(QIcon("Resources/spooky.ico"));

    MainWindow *mainWindow = new MainWindow;

    // add the mainwindow to our custom frameless window
    framelessWindow.setContent(mainWindow);
    framelessWindow.show();

    int ret = app.exec();

    AppManager::DestroyInstance();

    return ret;
}
