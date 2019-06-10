#ifndef SCENERENDERERMANAGER_H
#define SCENERENDERERMANAGER_H

#include <vector>

#include "Renderers/renderer.h"

class Camera3D;
class RenderTargetRenderer;
class RenderTarget;

enum RenderingBuffer
{
    BUFFER_ALL,
    BUFFER_POSITION,
    BUFFER_NORMALS,
    BUFFER_ALBEDO,
    BUFFER_DEPTH,
};

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

    void BindRenderTarget(int w, int h);
    void BindRenderTarget();
    void UnbindRenderTarget();

    void RenderOnCamera();
    void RenderOnCamera(int w, int h);

    void RenderRenderTarget();

    void SetRenderingBuffer(RenderingBuffer buffer);
    RenderingBuffer GetRenderingBuffer();

private:
    Renderer *AddRenderer(Renderer* render);

    void DestroyAllRenderers();

private:
    std::vector<Renderer*> renderers;

    RenderTargetRenderer* render_target_renderer = nullptr;
    RenderTarget* render_target = nullptr;

    int last_w = 0;
    int last_h = 0;

    RenderingBuffer rendering_buffer = RenderingBuffer::BUFFER_ALL;
};

#endif // SCENERENDERERMANAGER_H
