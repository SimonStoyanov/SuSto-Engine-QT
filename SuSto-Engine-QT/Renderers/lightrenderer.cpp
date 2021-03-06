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

    std::string vert_path = base_path + "DirectionalLightVert.vert";
    Shader* ver_sha = ShaderManager::Instance()->LoadShaderFromFile(vert_path, ShaderType::VERTEX);

    std::string frag_path = base_path + "DirectionalLightFrag.frag";
    Shader* frag_sha = ShaderManager::Instance()->LoadShaderFromFile(frag_path, ShaderType::FRAGMENT);

    program = ShaderManager::Instance()->CreateShaderProgram();
    program->AddShader(ver_sha);
    program->AddShader(frag_sha);

    program->LinkProgram();
}

void LightRenderer::Render(Camera3D *camera, const float4x4 &view, const float4x4 &projection, RenderTarget *target)
{
    RenderDirectionals(camera, view, projection, target);
}

void LightRenderer::CleanUp()
{

}

void LightRenderer::RenderDirectionals(Camera3D *camera, const float4x4 &view, const float4x4 &projection, RenderTarget *target)
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
            if(1)
            {
                float3 light_colour = light->GetLightColour();
                float light_intensity = light->GetLightIntensity();

                Quat rotation = Quat::FromEulerXYZ(DEGTORAD(transform->GetRotationDegrees().x), DEGTORAD(transform->GetRotationDegrees().y),
                                                   DEGTORAD(transform->GetRotationDegrees().z));

                float3 rotation_degrees = transform->GetRotationDegrees();
                float3 rotation_rads = float3(DEGTORAD(rotation_degrees.x), DEGTORAD(rotation_degrees.y), DEGTORAD(rotation_degrees.z));

                float3 direction = float3::zero;
                direction.x = -cos(rotation_rads.z) * sin(rotation_rads.y) * sin(rotation_rads.x) * -sin(rotation_rads.z) * cos(rotation_rads.x);
                direction.y = -sin(rotation_rads.z) * sin(rotation_rads.y) * sin(rotation_rads.x)+cos(rotation_rads.z) * cos(rotation_rads.x);
                direction.z =  cos(rotation_rads.y) * sin(rotation_rads.x);

                float4x4 transform_mat = float4x4::FromTRS(transform->GetPos(), rotation, transform->GetScale());

                float4x4 world_transform = transform_mat;

                RenderManager::Instance()->BindVertexArrayBuffer(plane_mesh->GetVao());

                RenderManager::Instance()->SetUniformMatrix(program->GetID(), "View", view.ptr());
                RenderManager::Instance()->SetUniformMatrix(program->GetID(), "Projection", projection.ptr());

                RenderManager::Instance()->SetUniformMatrix(program->GetID(), "Model", world_transform.Transposed().ptr());

                RenderManager::Instance()->SetUniformVec3(program->GetID(), "CameraPos", camera->GetPosition());
                RenderManager::Instance()->SetUniformVec3(program->GetID(), "LightDir", direction);
                RenderManager::Instance()->SetUniformVec3(program->GetID(), "LightColour", light_colour);
                RenderManager::Instance()->SetUniformFloat(program->GetID(), "LightIntensity", light_intensity);

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

                RenderManager::Instance()->DrawElements(GL_TRIANGLES, plane_mesh->GetElementsCount());

                RenderManager::Instance()->UnbindVertexArrayBuffer();
            }
        }
    }

    program->StopUsingProgram();

    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}
