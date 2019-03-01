#ifndef APPMANAGER_H
#define APPMANAGER_H


class AppManager
{
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

private:
     static AppManager* instance;
};

#endif // APPMANAGER_H
