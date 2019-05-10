#ifndef SCENERENDERERMANAGER_H
#define SCENERENDERERMANAGER_H

#include <vector>

#include "Renderers/renderer.h"

class SceneRendererManager
{
    friend class AppManager;

private:
    SceneRendererManager();
    void operator delete(void *) {}

public:
    static SceneRendererManager* Instance()
    {
        if(instance == nullptr)
        {
            instance = new SceneRendererManager();
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

private:
    static SceneRendererManager* instance;

public:
    void StartRenderers();

    void RenderOnCamera();

private:
    Renderer *AddRenderer(Renderer* render);

    void DestroyAllRenderers();

private:
    std::vector<Renderer*> renderers;
};

#endif // SCENERENDERERMANAGER_H
