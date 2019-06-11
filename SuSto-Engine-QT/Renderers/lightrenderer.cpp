#include "lightrenderer.h"
#include "Managers/shadermanager.h"
#include "Managers/rendermanager.h"
#include "Renderers/rendertarget.h"
#include "Managers/meshmanager.h"
#include "Renderers/mesh.h"
#include "Managers/scenerenderermanager.h"
#include "Managers/entitymanager.h"
#include "Entity/entity.h"
#include "Entity/Components/c_light.h"
#include "Entity/Components/c_transform.h"
#include "Entity/Components/c_mesh_renderer.h"
#include "Managers/cameramanager.h"

LightRenderer::LightRenderer()
{

}

void LightRenderer::Start()
{
    plane_mesh = MeshManager::Instance()->vertical_plane_mesh;
    sphere_mesh = MeshManager::Instance()->sphere_mesh;

    std::string base_path = ShaderManager::Instance()->GetShadersBaseFolder();

    std::string vert_path = base_path + "LightVert.vert";
    Shader* ver_sha = ShaderManager::Instance()->LoadShaderFromFile(vert_path, ShaderType::VERTEX);

    std::string frag_path = base_path + "LightFrag.frag";
    Shader* frag_sha = ShaderManager::Instance()->LoadShaderFromFile(frag_path, ShaderType::FRAGMENT);

    program = ShaderManager::Instance()->CreateShaderProgram();
    program->AddShader(ver_sha);
    program->AddShader(frag_sha);

    program->LinkProgram();
}

void LightRenderer::Render(Camera3D *camera, const float4x4 &view, const float4x4 &projection, RenderTarget *target)
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glDepthFunc(GL_LESS);

    program->UseProgram();

    std::vector<Entity*> entities = EntityManager::Instance()->GetEntities();

    for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        C_Transform* transform = (*it)->GetTransform();
        C_Light* light = (C_Light*)(*it)->GetComponent(ComponentType::COMPONENT_LIGHT);

        if(light != nullptr)
        {
            Quat rotation = Quat::FromEulerXYZ(DEGTORAD(transform->GetRotationDegrees().x), DEGTORAD(transform->GetRotationDegrees().y),
                                               DEGTORAD(transform->GetRotationDegrees().z));

            float4x4 transform_mat = float4x4::FromTRS(transform->GetPos(), rotation, transform->GetScale());

            RenderManager::Instance()->BindVertexArrayBuffer(sphere_mesh->GetVao());

            RenderManager::Instance()->SetUniformMatrix(program->GetID(), "View", view.ptr());
            RenderManager::Instance()->SetUniformMatrix(program->GetID(), "Projection", projection.ptr());

            float4 colour = float4(1, 1, 1, 1);

            float4x4 world_transform = transform_mat;

            RenderManager::Instance()->SetUniformMatrix(program->GetID(), "Model", world_transform.Transposed().ptr());

            RenderManager::Instance()->SetUniformVec3(program->GetID(), "LightPos", transform->GetPos());
            RenderManager::Instance()->SetUniformVec3(program->GetID(), "CameraPos", camera->GetPosition());

            RenderManager::Instance()->DrawElements(GL_TRIANGLES, sphere_mesh->GetElementsCount());

            RenderManager::Instance()->UnbindVertexArrayBuffer();
        }
    }

    program->StopUsingProgram();

    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}

void LightRenderer::CleanUp()
{

}
