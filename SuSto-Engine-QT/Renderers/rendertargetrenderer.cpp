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

RenderTargetRenderer::RenderTargetRenderer()
{

}

void RenderTargetRenderer::Start()
{
    SPOOKYLOG("");
    SPOOKYLOG("DEFAULT PLANE ----------");

    plane_mesh = new Mesh("plane_default");

    plane_mesh->vertex_buffer.push_back(-1);
    plane_mesh->vertex_buffer.push_back(-1);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);

    plane_mesh->vertex_buffer.push_back(1);
    plane_mesh->vertex_buffer.push_back(-1);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(1);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);

    plane_mesh->vertex_buffer.push_back(1);
    plane_mesh->vertex_buffer.push_back(1);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(1);
    plane_mesh->vertex_buffer.push_back(1);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);

    plane_mesh->vertex_buffer.push_back(-1);
    plane_mesh->vertex_buffer.push_back(1);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(1);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);
    plane_mesh->vertex_buffer.push_back(0);

    plane_mesh->index_buffer.push_back(0);
    plane_mesh->index_buffer.push_back(1);
    plane_mesh->index_buffer.push_back(3);
    plane_mesh->index_buffer.push_back(1);
    plane_mesh->index_buffer.push_back(2);
    plane_mesh->index_buffer.push_back(3);


    MeshManager::Instance()->LoadToVRAM(plane_mesh);

    SPOOKYLOG("DEFAULT PLANE  ----------");
    SPOOKYLOG("");

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

void RenderTargetRenderer::Render(const float4x4 &view, const float4x4 &projection)
{
    glEnable(GL_BLEND);
    glDepthFunc(GL_LESS);

    program->UseProgram();

    RenderingBuffer curr_buffer = SceneRendererManager::Instance()->GetRenderingBuffer();

    if(render_target != nullptr)
    {
        RenderManager::Instance()->BindVertexArrayBuffer(plane_mesh->GetVao());

        RenderManager::Instance()->SetUniformMatrix(program->GetID(), "View", view.ptr());
        RenderManager::Instance()->SetUniformMatrix(program->GetID(), "Projection", projection.ptr());

        float4x4 model = float4x4::FromTRS(float3::zero, Quat::identity, float3(10, 10, 1));

        RenderManager::Instance()->SetUniformMatrix(program->GetID(), "Model", model.Transposed().ptr());

        switch (curr_buffer)
        {
            case RenderingBuffer::BUFFER_POSITION:
            {
                RenderManager::Instance()->SetActiveTexture(GL_TEXTURE0);
                RenderManager::Instance()->BindTexture(render_target->GetPositionColorTextureId());
                break;
            }
            case RenderingBuffer::BUFFER_NORMALS:
            {
                RenderManager::Instance()->SetActiveTexture(GL_TEXTURE0);
                RenderManager::Instance()->BindTexture(render_target->GetNormalColorTextureId());
                break;
            }
            case RenderingBuffer::BUFFER_ALBEDO:
            {
                RenderManager::Instance()->SetActiveTexture(GL_TEXTURE0);
                RenderManager::Instance()->BindTexture(render_target->GetColorPlusSpecularColorTextureId());
                break;
            }
            case RenderingBuffer::BUFFER_DEPTH:
            {
                RenderManager::Instance()->SetActiveTexture(GL_TEXTURE0);
                RenderManager::Instance()->BindTexture(render_target->GetDepthTextureId());
                break;
            }
        }

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

void RenderTargetRenderer::SetTarget(RenderTarget* target)
{
    render_target = target;
}
