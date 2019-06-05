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
        }

        return instance;
    }

    static void DestroyInstance()
    {
        if(instance != nullptr)
        {
            delete instance;

            instance = nullptr;
        }
    }

    void Init(QApplication& app);
    void Start(QApplication& app);
    void CleanUp(QApplication& app);

    const float GetDT() const
    {
        return dt;
    }

private slots:
    void Update();

private:
     static AppManager* instance;

     QTimer workTimer;
     QTime dtTimer;

     float dt = 0.0f;
};

#endif // APPMANAGER_H
