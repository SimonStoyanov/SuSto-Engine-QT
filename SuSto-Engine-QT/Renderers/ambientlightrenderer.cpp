#include "ambientlightrenderer.h"
#include "Managers/shadermanager.h"
#include "Managers/rendermanager.h"
#include "Renderers/rendertarget.h"
#include "Managers/meshmanager.h"
#include "Renderers/mesh.h"
#include "Managers/scenerenderermanager.h"

AmbientLightRenderer::AmbientLightRenderer()
{

}

void AmbientLightRenderer::Start()
{
    plane_mesh = MeshManager::Instance()->vertical_plane_mesh;

    std::string base_path = ShaderManager::Instance()->GetShadersBaseFolder();

    std::string vert_path = base_path + "AmbientLightVert.vert";
    Shader* ver_sha = ShaderManager::Instance()->LoadShaderFromFile(vert_path, ShaderType::VERTEX);

    std::string frag_path = base_path + "AmbientLightFrag.frag";
    Shader* frag_sha = ShaderManager::Instance()->LoadShaderFromFile(frag_path, ShaderType::FRAGMENT);

    program = ShaderManager::Instance()->CreateShaderProgram();
    program->AddShader(ver_sha);
    program->AddShader(frag_sha);

    program->LinkProgram();
}

void AmbientLightRenderer::Render(Camera3D *camera, const float4x4 &view, const float4x4 &projection, RenderTarget* target)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glDepthFunc(GL_LESS);

    program->UseProgram();

    RenderManager::Instance()->BindVertexArrayBuffer(plane_mesh->GetVao());

    float intensity = SceneRendererManager::Instance()->GetAmbientLight();

    RenderManager::Instance()->SetUniformFloat(program->GetID(), "ambient_intensity", intensity);

    RenderManager::Instance()->SetActiveTexture(GL_TEXTURE0);
    RenderManager::Instance()->BindTexture(target->GetColorPlusSpecularColorTextureId());

    RenderManager::Instance()->DrawElements(GL_TRIANGLES, plane_mesh->GetElementsCount());

    program->StopUsingProgram();

    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}

void AmbientLightRenderer::CleanUp()
{

}
