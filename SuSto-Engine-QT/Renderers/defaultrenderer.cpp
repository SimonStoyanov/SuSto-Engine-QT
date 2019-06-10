#include "defaultrenderer.h"
#include "Renderers/vertexbuffer.h"
#include "Managers/shadermanager.h"
#include "Managers/rendermanager.h"
#include "Managers/meshmanager.h"
#include "Renderers/mesh.h"
#include "Managers/entitymanager.h"
#include "Entity/Components/c_mesh_renderer.h"
#include "Entity/Components/c_transform.h"
#include "Entity/Components/c_material_renderer.h"
#include "Renderers/texture.h"
#include "qdir.h"
#include "qcoreapplication.h"

DefaultRenderer::DefaultRenderer()
{

}

void DefaultRenderer::Start()
{
    std::string base_path = ShaderManager::Instance()->GetShadersBaseFolder();

    std::string vert_path = base_path + "DefaultVert.vert";
    Shader* ver_sha = ShaderManager::Instance()->LoadShaderFromFile(vert_path, ShaderType::VERTEX);

    std::string frag_path = base_path + "DefaultFrag.frag";
    Shader* frag_sha = ShaderManager::Instance()->LoadShaderFromFile(frag_path, ShaderType::FRAGMENT);

    program = ShaderManager::Instance()->CreateShaderProgram();
    program->AddShader(ver_sha);
    program->AddShader(frag_sha);

    program->LinkProgram();
}

void DefaultRenderer::Render(const float4x4 &view, const float4x4 &projection)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glDepthFunc(GL_LESS);

    program->UseProgram();

    std::vector<Entity*> entities = EntityManager::Instance()->GetEntities();

    for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        C_Transform* transform = (*it)->GetTransform();
        C_MeshRenderer* mesh_renderer = (C_MeshRenderer*)(*it)->GetComponent(ComponentType::COMPONENT_MESH_RENDERER);
        C_MaterialRenderer* material_renderer = (C_MaterialRenderer*)(*it)->GetComponent(ComponentType::COMPONENT_MATERIAL_RENDERER);

        bool has_diffuse = false;
        bool has_normal = false;
        bool has_height = false;
        bool has_specular = false;

        if(material_renderer != nullptr)
        {
            if(material_renderer->GetDiffuseTexture() != nullptr)
                has_diffuse = true;

            if(material_renderer->GetNormalTexture() != nullptr)
                has_normal = true;

            if(material_renderer->GetHeightTexture() != nullptr)
                has_height = true;

            if(material_renderer->GetSpecularTexture() != nullptr)
                has_specular = true;
        }

        Quat rotation = Quat::FromEulerXYZ(DEGTORAD(transform->GetRotationDegrees().x), DEGTORAD(transform->GetRotationDegrees().y),
                                           DEGTORAD(transform->GetRotationDegrees().z));

        float4x4 transform_mat = float4x4::FromTRS(transform->GetPos(), rotation, transform->GetScale());

        if(mesh_renderer != nullptr)
        {
            Mesh* curr_mesh = mesh_renderer->GetMesh();

            if(curr_mesh != nullptr)
            {
                if(curr_mesh->GetLoaded())
                {
                    RenderManager::Instance()->BindVertexArrayBuffer(curr_mesh->GetVao());

                    RenderManager::Instance()->SetUniformMatrix(program->GetID(), "View", view.ptr());
                    RenderManager::Instance()->SetUniformMatrix(program->GetID(), "Projection", projection.ptr());

                    float4 colour = float4(1, 1, 1, 1);

                    float4x4 world_transform = transform_mat;

                    RenderManager::Instance()->SetUniformVec4(program->GetID(), "col", colour);
                    RenderManager::Instance()->SetUniformInt(program->GetID(), "hasDiffuse", has_diffuse);
                    RenderManager::Instance()->SetUniformInt(program->GetID(), "hasNormalMap", has_normal);
                    RenderManager::Instance()->SetUniformInt(program->GetID(), "hasAlbedo", has_specular);

                    RenderManager::Instance()->SetUniformMatrix(program->GetID(), "Model", world_transform.Transposed().ptr());

                    if(has_diffuse)
                    {
                         RenderManager::Instance()->SetActiveTexture(GL_TEXTURE0);
                         RenderManager::Instance()->BindTexture(material_renderer->GetDiffuseTexture()->GetTextureId());
                    }

                    if(has_normal)
                    {
                         RenderManager::Instance()->SetActiveTexture(GL_TEXTURE1);
                         RenderManager::Instance()->BindTexture(material_renderer->GetNormalTexture()->GetTextureId());
                    }

                    if(has_specular)
                    {
                         RenderManager::Instance()->SetActiveTexture(GL_TEXTURE2);
                         RenderManager::Instance()->BindTexture(material_renderer->GetSpecularTexture()->GetTextureId());
                    }

                    RenderManager::Instance()->DrawElements(GL_TRIANGLES, curr_mesh->GetElementsCount());

                    RenderManager::Instance()->UnbindVertexArrayBuffer();
                }

            }
        }
    }

    //program->StopUsingProgram();

    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}

void DefaultRenderer::CleanUp()
{
    ShaderManager::Instance()->DestroyShaderProgram(program);
}
