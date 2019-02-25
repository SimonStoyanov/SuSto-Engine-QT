#-------------------------------------------------
#
# Project created by QtCreator 2019-02-22T12:49:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): DEFINES += ADS_NAMESPACE_ENABLED

windows {
        # MinGW
        *-g++* {
                QMAKE_CXXFLAGS += -std=c++11
        }
        # MSVC
        *-msvc* {
        }
}

INCLUDEPATH += "3rdParty/DarkStyle/framelesswindow"

TARGET = SuSto-Engine-QT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        rendererwidget.cpp \
        3rdParty/DarkStyle/framelesswindow/framelesswindow.cpp \
        3rdParty/DarkStyle/framelesswindow/windowdragger.cpp \
        3rdParty/DarkStyle/DarkStyle.cpp \
    hierarchy.cpp \
    entity.cpp \
    entity.cpp \
    component.cpp

HEADERS += \
        mainwindow.h \
        rendererwidget.h \
        3rdParty/DarkStyle/framelesswindow/framelesswindow.h \
        3rdParty/DarkStyle/framelesswindow/windowdragger.h \
        3rdParty/DarkStyle/DarkStyle.h \
    hierarchy.h \
    entity.h \
    component.h

FORMS += \
        mainwindow.ui \
        3rdParty/DarkStyle/framelesswindow/framelesswindow.ui \
    hierarchy.ui

QT += opengl \

RC_FILE = myapp.rc \

CONFIG += console

RESOURCES += 3rdParty/DarkStyle/framelesswindow.qrc \
             3rdParty/DarkStyle/darkstyle.qrc

# Dependency: AdvancedDockingSystem (staticlib)
#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../AdvancedDockingSystem/release/ -lAdvancedDockingSystem
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../AdvancedDockingSystem/debug/ -lAdvancedDockingSystem
#else:unix: LIBS += -L$$OUT_PWD/../AdvancedDockingSystem/ -lAdvancedDockingSystem

#INCLUDEPATH += $$PWD/../AdvancedDockingSystem/include
#DEPENDPATH += $$PWD/../AdvancedDockingSystem/include

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AdvancedDockingSystem/release/libAdvancedDockingSystem.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AdvancedDockingSystem/debug/libAdvancedDockingSystem.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AdvancedDockingSystem/release/AdvancedDockingSystem.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AdvancedDockingSystem/debug/AdvancedDockingSystem.lib
#else:unix: PRE_TARGETDEPS += $$OUT_PWD/../AdvancedDockingSystem/libAdvancedDockingSystem.a

# Dependency: AdvancedDockingSystem (shared)
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../build-AdvancedDockingSystem-Desktop_Qt_5_10_0_MSVC2017_64bit-Debug/release/ -lAdvancedDockingSystem1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../build-AdvancedDockingSystem-Desktop_Qt_5_10_0_MSVC2017_64bit-Debug/debug/ -lAdvancedDockingSystem1
else:unix: LIBS += -L$$OUT_PWD/../build-AdvancedDockingSystem-Desktop_Qt_5_10_0_MSVC2017_64bit-Debug/ -lAdvancedDockingSystem1

INCLUDEPATH += $$PWD/../AdvancedDockingSystem/include
DEPENDPATH += $$PWD/../AdvancedDockingSystem/include
