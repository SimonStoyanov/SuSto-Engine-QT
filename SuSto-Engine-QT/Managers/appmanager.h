#ifndef APPMANAGER_H
#define APPMANAGER_H

#include "QTimer"
#include "QWidget"

class AppManager : public QObject
{
    Q_OBJECT

private:
    AppManager();
    void operator delete(void *) {}

public:
    static AppManager* Instance()
    {
        if(instance == nullptr)
        {
            instance = new AppManager();

            instance->Start();
        }

        return instance;
    }

    static void DestroyInstance()
    {
        if(instance != nullptr)
        {
            instance->CleanUp();

            delete instance;

            instance = nullptr;
        }
    }

    void Init();

private:
    void Start();
    void CleanUp();

private slots:
    void Update();

private:
     static AppManager* instance;

     QTimer workTimer;
};

#endif // APPMANAGER_H
