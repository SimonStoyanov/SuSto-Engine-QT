#include "scenerenderermanager.h"
#include "Renderers/geometryrenderer.h"
#include "Renderers/rendertargetrenderer.h"
#include "Managers/cameramanager.h"
#include "Renderers/rendertarget.h"
#include "Renderers/ambientlightrenderer.h"
#include "Managers/meshmanager.h"
#include "Managers/rendermanager.h"
#include "Renderers/lightrenderer.h"
#include "globals.h"

SceneRendererManager* SceneRendererManager::instance = nullptr;

SceneRendererManager::SceneRendererManager()
{

}

void SceneRendererManager::Start()
{

}

void SceneRendererManager::CleanUp()
{
    DestroyAllRenderers();
}

void SceneRendererManager::StartRenderers()
{
    MeshManager::Instance()->LoadDefaultMeshes();

    render_target = new RenderTarget();
    render_target->Start();

    render_target_renderer = new RenderTargetRenderer();
    render_target_renderer->Start();

    geometry_renderer = new GeometryRenderer();
    geometry_renderer->Start();

    ambient_light_renderer = new AmbientLightRenderer();
    ambient_light_renderer->Start();

    light_renderer = new LightRenderer();
    light_renderer->Start();
}

void SceneRendererManager::ResizeRenderTarget(int w, int h)
{
    render_target->Resize(float2(w, h));
}

void SceneRendererManager::RenderOnCamera()
{    
    RenderOnCamera(last_w, last_h);
}

void SceneRendererManager::RenderOnCamera(int w, int h)
{
    if(last_w != w || last_h != h)
    {
        float ratio = (float)w / (float)h;
        CameraManager::Instance()->GetEditorCamera()->SetAspectRatio(ratio);

        last_w = w;
        last_h = h;
    } 

    Camera3D* editor_camera = CameraManager::Instance()->GetEditorCamera();

    float4x4 view_mat = editor_camera->GetOpenGLViewMatrix();
    float4x4 proj_mat = editor_camera->GetOpenGLProjectionMatrix();

    render_target->Bind();

    RenderManager::Instance()->Clear();

    geometry_renderer->Render(editor_camera, view_mat, proj_mat, render_target);

    render_target->UnBind();

    render_target->Bind();

    ambient_light_renderer->Render(editor_camera, view_mat, proj_mat, render_target);

    render_target->UnBind();

    render_target->Bind();

    light_renderer->Render(editor_camera, view_mat, proj_mat, render_target);

    render_target->UnBind();
}

void SceneRendererManager::RenderRenderTarget()
{
    Camera3D* editor_camera = CameraManager::Instance()->GetEditorCamera();

    float4x4 view_mat = editor_camera->GetOpenGLViewMatrix();
    float4x4 proj_mat = editor_camera->GetOpenGLProjectionMatrix();

    render_target_renderer->Render(editor_camera, view_mat, proj_mat, render_target);
}

void SceneRendererManager::SetRenderingBuffer(RenderingBuffer buffer)
{
    rendering_buffer = buffer;
}

RenderingBuffer SceneRendererManager::GetRenderingBuffer()
{
    return rendering_buffer;
}

void SceneRendererManager::SetAmbientLight(float set)
{
    ambient_light = set;

    if(ambient_light < 0)
    {
        ambient_light = 0;
    }
}

float SceneRendererManager::GetAmbientLight() const
{
    return ambient_light;
}

Renderer *SceneRendererManager::AddRenderer(Renderer *renderer)
{
    Renderer* ret = nullptr;

    if(renderer != nullptr)
    {
        renderers.push_back(renderer);

        renderer->Start();
    }

    return ret;
}

void SceneRendererManager::DestroyAllRenderers()
{
    for(std::vector<Renderer*>::iterator it = renderers.begin(); it != renderers.end(); ++it)
    {
        (*it)->CleanUp();
    }

    renderers.clear();
}
