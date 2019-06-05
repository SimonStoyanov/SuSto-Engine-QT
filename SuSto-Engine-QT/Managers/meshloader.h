#ifndef MESHLOADER_H
#define MESHLOADER_H

class MeshLoader
{
    friend class AppManager;

private:
    MeshLoader();
    void operator delete(void *) {}

public:
    static MeshLoader* Instance()
    {
        if(instance == nullptr)
        {
            instance = new MeshLoader();
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

private:
    void Start();
    void CleanUp();

    void DestroyAllEventDelegates();

private:
    static MeshLoader* instance;
};

#endif // MESHLOADER_H
