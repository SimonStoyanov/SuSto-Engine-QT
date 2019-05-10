#include "scenerenderermanager.h"
#include "Renderers/defaultrenderer.h"
#include "Managers/cameramanager.h"

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
    AddRenderer(new DefaultRenderer());
}

void SceneRendererManager::RenderOnCamera()
{
    float4x4 view_mat = CameraManager::Instance()->GetEditorCamera()->GetOpenGLViewMatrix();
    float4x4 proj_mat = CameraManager::Instance()->GetEditorCamera()->GetOpenGLProjectionMatrix();
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
