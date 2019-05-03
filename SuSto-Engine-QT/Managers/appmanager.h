#ifndef APPMANAGER_H
#define APPMANAGER_H

#include "QTime"
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

    const float GetDT() const {
        return dt;
    }

private:
    void Start();
    void CleanUp();

private slots:
    void Update();

private:
     static AppManager* instance;

     QTimer workTimer;
     QTime dtTimer;

     float dt;
};

#endif // APPMANAGER_H
