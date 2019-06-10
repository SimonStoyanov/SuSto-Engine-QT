#include "scenerenderermanager.h"
#include "Renderers/defaultrenderer.h"
#include "Renderers/rendertargetrenderer.h"
#include "Managers/cameramanager.h"
#include "Renderers/rendertarget.h"
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
    render_target = new RenderTarget();
    render_target->Start();

    render_target_renderer = new RenderTargetRenderer();
    render_target_renderer->Start();

    AddRenderer(new DefaultRenderer());
}

void SceneRendererManager::BindRenderTarget()
{
    BindRenderTarget(last_w, last_h);
}
void SceneRendererManager::BindRenderTarget(int w, int h)
{
    render_target->Resize(float2(w, h));

    render_target->Bind();
}

void SceneRendererManager::UnbindRenderTarget()
{
    render_target->UnBind();
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

    float4x4 view_mat = CameraManager::Instance()->GetEditorCamera()->GetOpenGLViewMatrix();
    float4x4 proj_mat = CameraManager::Instance()->GetEditorCamera()->GetOpenGLProjectionMatrix();

    for(std::vector<Renderer*>::iterator it = renderers.begin(); it != renderers.end(); ++it)
    {
        (*it)->Render(view_mat, proj_mat);
    }
}

void SceneRendererManager::RenderRenderTarget()
{
    float4x4 view_mat = CameraManager::Instance()->GetEditorCamera()->GetOpenGLViewMatrix();
    float4x4 proj_mat = CameraManager::Instance()->GetEditorCamera()->GetOpenGLProjectionMatrix();

    render_target_renderer->SetTarget(render_target);
    render_target_renderer->Render(view_mat, proj_mat);
}

void SceneRendererManager::SetRenderingBuffer(RenderingBuffer buffer)
{
    rendering_buffer = buffer;
}

RenderingBuffer SceneRendererManager::GetRenderingBuffer()
{
    return rendering_buffer;
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
