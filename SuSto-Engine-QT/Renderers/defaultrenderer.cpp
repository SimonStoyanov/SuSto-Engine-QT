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

DefaultRenderer::DefaultRenderer()
{

}

void DefaultRenderer::Start()
{
    const char* vertex_code =
    "#version 330 core\n \
    layout(location = 0) in vec3 position; \n \
    layout(location = 1) in vec3 normals; \n \
    layout(location = 2) in vec2 uvs; \n \
    layout(location = 3) in vec3 tangents; \n \
    layout(location = 4) in vec3 bitangents; \n \
    \
    uniform mat4 Model; \
    uniform mat4 View; \
    uniform mat4 Projection; \
    \
    uniform float ambientTerm; \
    \
    uniform vec4 col; \
    uniform int hasDiffuse; \
    uniform int hasNormalMap; \
    \
    \
    out Data \
    { \
     mat4 worldViewMatrix; \
     vec3 tangentLocalspace; \
     vec3 bitangentLocalspace; \
     vec3 normalLocalspace; \
     vec2 uvs; \
     vec4 colour; \
     flat int hasDiffuse; \
     flat int hasNormalMap; \
     float ambientTerm; \
    } VSOut; \
    \
    void main()\
    {\
        \
        VSOut.worldViewMatrix = View * Model; \
        VSOut.tangentLocalspace = tangents; \
        VSOut.bitangentLocalspace = bitangents; \
        VSOut.normalLocalspace = normals; \
        VSOut.uvs = uvs; \
        VSOut.colour = col; \
        VSOut.hasDiffuse = hasDiffuse; \
        VSOut.hasNormalMap = hasNormalMap; \
        VSOut.ambientTerm = ambientTerm; \
        \
        gl_Position = Projection * View * Model * vec4(vec3(position.x, position.y, position.z), 1);\
    }";

    const char* fragment_code =
    "#version 330 core\n \
    uniform sampler2D diffuse; \
    uniform sampler2D normalMap; \
    \
    out vec4 finalColor; \
    \
    in Data \
    {\
     mat4 worldViewMatrix; \
     vec3 tangentLocalspace; \
     vec3 bitangentLocalspace; \
     vec3 normalLocalspace; \
     vec2 uvs; \
     vec4 colour; \
     flat int hasDiffuse; \
     flat int hasNormalMap; \
     float ambientTerm; \
    } FSIn; \
    \
    void main()\
    {\
        if(FSIn.hasNormalMap == 1) \
        {\
            vec3 T = normalize(FSIn.tangentLocalspace); \
            vec3 B = normalize(FSIn.bitangentLocalspace); \
            vec3 N = normalize(FSIn.normalLocalspace); \
            mat3 TBN = mat3(T, B, N); \
            \
            vec3 tangentSpaceNormal = texture(normalMap, FSIn.uvs).xyz * 2.0 - vec3(1.0); \
            vec3 localSpaceNormal = TBN * tangentSpaceNormal; \
            vec3 viewSpaceNormal = normalize(FSIn.worldViewMatrix * vec4(localSpaceNormal, 0.0)).xyz; \
        }\
        \
        vec4 diffuse_col; \
        \
        if(FSIn.hasDiffuse == 1)\
        {\
            diffuse_col = texture(diffuse, FSIn.uvs);\
        }\
        else\
        {\
            diffuse_col = FSIn.colour;\
        }\
        \
        finalColor.a = diffuse_col.a; \
        finalColor.rgb = diffuse_col.rgb * FSIn.ambientTerm; \; \
        \
    }";

    Shader* vsh = ShaderManager::Instance()->CreateShader(ShaderType::VERTEX);
    vsh->SetShaderCode(vertex_code);

    Shader* fsh = ShaderManager::Instance()->CreateShader(ShaderType::FRAGMENT);
    fsh->SetShaderCode(fragment_code);

    program = ShaderManager::Instance()->CreateShaderProgram();
    program->AddShader(vsh);
    program->AddShader(fsh);

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

        if(material_renderer != nullptr)
        {
            if(material_renderer->GetDiffuseTexture() != nullptr)
                has_diffuse = true;

            if(material_renderer->GetNormalTexture() != nullptr)
                has_normal = true;

            if(material_renderer->GetHeightTexture() != nullptr)
                has_height = true;
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

                    RenderManager::Instance()->SetUniformMatrix(program->GetID(), "Model", world_transform.Transposed().ptr());

                    RenderManager::Instance()->SetUniformFloat(program->GetID(), "ambientTerm", 0.35f);

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
