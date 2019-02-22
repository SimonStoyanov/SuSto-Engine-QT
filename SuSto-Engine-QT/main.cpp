#include "mainwindow.h"
#include <QApplication>
#include "3rdParty/DarkStyle/framelesswindow/framelesswindow.h"
#include "3rdParty/DarkStyle/DarkStyle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyle(new DarkStyle);

    FramelessWindow framelessWindow;
    framelessWindow.setWindowIcon(QIcon("Resources/spooky.ico"));

    MainWindow *mainWindow = new MainWindow;

    // add the mainwindow to our custom frameless window
    framelessWindow.setContent(mainWindow);
    framelessWindow.show();

    return a.exec();
}
