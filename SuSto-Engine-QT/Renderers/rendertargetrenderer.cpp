#include "rendertargetrenderer.h"
#include "Renderers/vertexbuffer.h"
#include "Managers/shadermanager.h"
#include "Managers/rendermanager.h"
#include "Managers/meshmanager.h"
#include "Renderers/mesh.h"
#include "Managers/entitymanager.h"
#include "Entity/Components/c_mesh_renderer.h"
#include "Entity/Components/c_transform.h"
#include "Renderers/rendertarget.h"
#include "Managers/scenerenderermanager.h"
#include "Managers/cameramanager.h"
#include "Managers/meshmanager.h"

RenderTargetRenderer::RenderTargetRenderer()
{

}

void RenderTargetRenderer::Start()
{
    plane_mesh = MeshManager::Instance()->vertical_plane_mesh;

    std::string base_path = ShaderManager::Instance()->GetShadersBaseFolder();

    std::string vert_path = base_path + "RenderTargetVert.vert";
    Shader* ver_sha = ShaderManager::Instance()->LoadShaderFromFile(vert_path, ShaderType::VERTEX);

    std::string frag_path = base_path + "RenderTargetFrag.frag";
    Shader* frag_sha = ShaderManager::Instance()->LoadShaderFromFile(frag_path, ShaderType::FRAGMENT);

    program = ShaderManager::Instance()->CreateShaderProgram();
    program->AddShader(ver_sha);
    program->AddShader(frag_sha);

    program->LinkProgram();
}

void RenderTargetRenderer::Render(Camera3D* camera, const float4x4 &view, const float4x4 &projection, RenderTarget* target)
{
    glDisable(GL_BLEND);
    glDepthFunc(GL_LESS);

    program->UseProgram();

    float3 view_pos = camera->GetPosition();

    if(target != nullptr)
    {
        int mode = SceneRendererManager::Instance()->GetRenderingBuffer();

        RenderManager::Instance()->BindVertexArrayBuffer(plane_mesh->GetVao());

        RenderManager::Instance()->SetUniformMatrix(program->GetID(), "View", view.ptr());
        RenderManager::Instance()->SetUniformMatrix(program->GetID(), "Projection", projection.ptr());

        RenderManager::Instance()->SetUniformVec3(program->GetID(), "view_pos", view_pos);

        float4x4 model = float4x4::FromTRS(float3::zero, Quat::identity, float3(10, 10, 1));

        RenderManager::Instance()->SetUniformMatrix(program->GetID(), "Model", model.Transposed().ptr());

        RenderManager::Instance()->SetUniformInt(program->GetID(), "mode", mode);

        RenderManager::Instance()->SetUniformInt(program->GetID(), "gPosition", 0);
        RenderManager::Instance()->SetActiveTexture(GL_TEXTURE0);
        RenderManager::Instance()->BindTexture(target->GetPositionColorTextureId());

        RenderManager::Instance()->SetUniformInt(program->GetID(), "gNormal", 1);
        RenderManager::Instance()->SetActiveTexture(GL_TEXTURE1);
        RenderManager::Instance()->BindTexture(target->GetNormalColorTextureId());

        RenderManager::Instance()->SetUniformInt(program->GetID(), "gAlbedoSpec", 2);
        RenderManager::Instance()->SetActiveTexture(GL_TEXTURE2);
        RenderManager::Instance()->BindTexture(target->GetColorPlusSpecularColorTextureId());

        RenderManager::Instance()->SetUniformInt(program->GetID(), "gAmbient", 3);
        RenderManager::Instance()->SetActiveTexture(GL_TEXTURE3);
        RenderManager::Instance()->BindTexture(target->GetAmbientLightTextureId());

        RenderManager::Instance()->SetUniformInt(program->GetID(), "gLight", 4);
        RenderManager::Instance()->SetActiveTexture(GL_TEXTURE4);
        RenderManager::Instance()->BindTexture(target->GetLightTextureId());

        RenderManager::Instance()->DrawElements(GL_TRIANGLES, plane_mesh->GetElementsCount());

        RenderManager::Instance()->UnbindVertexArrayBuffer();
    }

    program->StopUsingProgram();

    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}

void RenderTargetRenderer::CleanUp()
{

}
