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

    const char* vertex_code =
    "#version 330 core\n \
    layout(location = 0) in vec3 position; \n \
    layout(location = 1) in vec3 normals; \n \
    layout(location = 2) in vec2 uvs; \n \
    \
    uniform mat4 Model; \
    uniform mat4 View; \
    uniform mat4 Projection; \
            \
    out vec2 oUvs; \
    \
    void main()\
    {\
        oUvs = uvs; \
        gl_Position = vec4(vec3(position.x, position.y, position.z), 1);\
    }";

    const char* fragment_code =
    "#version 330 core\n \
    uniform sampler2D tex; \
    in vec2 oUvs; \
    out vec4 finalColor; \
    void main() \
    {\
        finalColor = texture(tex, oUvs);\
    }";

    // finalCOlor = vec4(1, 1, 1, 1);

    Shader* vsh = ShaderManager::Instance()->CreateShader(ShaderType::VERTEX);
    vsh->SetShaderCode(vertex_code);

    Shader* fsh = ShaderManager::Instance()->CreateShader(ShaderType::FRAGMENT);
    fsh->SetShaderCode(fragment_code);

    program = ShaderManager::Instance()->CreateShaderProgram();
    program->AddShader(vsh);
    program->AddShader(fsh);

    program->LinkProgram();
}

void RenderTargetRenderer::Render(const float4x4 &view, const float4x4 &projection)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glDepthFunc(GL_LESS);

    program->UseProgram();

    if(render_target != nullptr)
    {
        RenderManager::Instance()->BindVertexArrayBuffer(plane_mesh->GetVao());

        RenderManager::Instance()->SetUniformMatrix(program->GetID(), "View", view.ptr());
        RenderManager::Instance()->SetUniformMatrix(program->GetID(), "Projection", projection.ptr());

        float4x4 model = float4x4::FromTRS(float3::zero, Quat::identity, float3(10, 10, 1));

        RenderManager::Instance()->SetUniformMatrix(program->GetID(), "Model", model.Transposed().ptr());

        RenderManager::Instance()->SetActiveTexture(GL_TEXTURE0);
        RenderManager::Instance()->BindTexture(render_target->GetColorTextureId());

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
