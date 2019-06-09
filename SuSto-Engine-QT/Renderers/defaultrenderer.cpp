#include "defaultrenderer.h"
#include "Renderers/vertexbuffer.h"
#include "Managers/shadermanager.h"
#include "Managers/rendermanager.h"
#include "Managers/meshmanager.h"
#include "Renderers/mesh.h"
#include "Managers/entitymanager.h"
#include "Entity/Components/c_mesh_renderer.h"
#include "Entity/Components/c_transform.h"

DefaultRenderer::DefaultRenderer()
{

}

void DefaultRenderer::Start()
{
    //Mesh* curr_mesh = MeshManager::Instance()->LoadMesh("C:/Users/Guillem/Desktop/PalmTree/PalmTree.obj");
    //MeshManager::Instance()->LoadToVRAM(curr_mesh);

    //Mesh* curr_mesh2 = MeshManager::Instance()->LoadMesh("C:/Users/Guillem/Desktop/Patrick/Patrick.obj");
    //MeshManager::Instance()->LoadToVRAM(curr_mesh2);

    const char* vertex_code =
    "#version 330 core\n \
    layout(location = 0) in vec3 position; \n \
    layout(location = 1) in vec3 normals; \n \
    layout(location = 2) in vec2 uvs; \n \
    \
    uniform mat4 Model; \
    uniform mat4 View; \
    uniform mat4 Projection; \
    uniform float z_pos; \
    \
    uniform vec4 col; \
    uniform int hasTexture; \
    out vec4 oCol; \
    flat out int oHasTexture; \
    out vec2 oUvs; \
    \
    void main()\
    {\
        oCol = col;\
        oHasTexture = hasTexture;\
        oUvs = uvs; \
        gl_Position = Projection * View * Model * vec4(vec3(position.x, position.y, position.z), 1);\
    }";

    const char* fragment_code =
    "#version 330 core\n \
    uniform sampler2D tex; \
    in vec4 oCol; \
    flat in int oHasTexture; \
    in vec2 oUvs; \
    out vec4 finalColor; \
    void main()\
    {\
        if(oHasTexture == 1)\
        {\
            finalColor = texture(tex, oUvs);\
        }\
        else\
        {\
            finalColor = oCol;\
        }\
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

        Quat rotation = Quat::FromEulerXYZ(DEGTORAD(transform->GetRotationDegrees().x), DEGTORAD(transform->GetRotationDegrees().y),
                                           DEGTORAD(transform->GetRotationDegrees().z));

        float4x4 transform_mat = float4x4::FromTRS(transform->GetPos(), rotation, transform->GetScale());

        if(mesh_renderer != nullptr)
        {
            Mesh* curr_mesh = mesh_renderer->GetMesh();

            if(curr_mesh != nullptr)
            {
                std::vector<SubMesh*> submeshes = curr_mesh->GetSubMeshes();

                for(std::vector<SubMesh*>::iterator it = submeshes.begin(); it != submeshes.end(); ++it)
                {
                    if((*it)->GetLoaded())
                    {
                        RenderManager::Instance()->BindVertexArrayBuffer((*it)->GetVao());

                        RenderManager::Instance()->SetUniformMatrix(program->GetID(), "View", view.ptr());
                        RenderManager::Instance()->SetUniformMatrix(program->GetID(), "Projection", projection.ptr());

                        float4 colour = float4(1, 1, 1, 1);

                        float4x4 world_transform = transform_mat;

                        RenderManager::Instance()->SetUniformFloat(program->GetID(), "z_pos", 1);

                        RenderManager::Instance()->SetUniformVec4(program->GetID(), "col", colour);
                        RenderManager::Instance()->SetUniformInt(program->GetID(), "hasTexture", false);

                        RenderManager::Instance()->SetUniformMatrix(program->GetID(), "Model", world_transform.Transposed().ptr());

                        RenderManager::Instance()->DrawElements(GL_TRIANGLES, (*it)->GetElementsCount());

                        RenderManager::Instance()->UnbindVertexArrayBuffer();
                    }
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
