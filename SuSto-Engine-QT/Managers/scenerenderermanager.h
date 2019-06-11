#ifndef SCENERENDERERMANAGER_H
#define SCENERENDERERMANAGER_H

#include <vector>

#include "Renderers/renderer.h"

class Camera3D;
class RenderTargetRenderer;
class GeometryRenderer;
class AmbientLightRenderer;
class LightRenderer;
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

    void ResizeRenderTarget(int w, int h);

    void RenderOnCamera();
    void RenderOnCamera(int w, int h);

    void RenderRenderTarget();

    void SetRenderingBuffer(RenderingBuffer buffer);
    RenderingBuffer GetRenderingBuffer();
    void SetAmbientLight(float set);
    float GetAmbientLight() const;

private:
    Renderer *AddRenderer(Renderer* render);

    void DestroyAllRenderers();

private:
    std::vector<Renderer*> renderers;

    GeometryRenderer* geometry_renderer = nullptr;
    AmbientLightRenderer* ambient_light_renderer = nullptr;
    LightRenderer* light_renderer = nullptr;
    RenderTargetRenderer* render_target_renderer = nullptr;
    RenderTarget* render_target = nullptr;

    int last_w = 0;
    int last_h = 0;

    RenderingBuffer rendering_buffer = RenderingBuffer::BUFFER_ALL;
    float ambient_light = 0.2f;
};

#endif // SCENERENDERERMANAGER_H
