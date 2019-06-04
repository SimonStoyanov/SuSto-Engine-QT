#include "defaultrenderer.h"
#include "Renderers/vertexbuffer.h"
#include "Managers/shadermanager.h"
#include "Managers/rendermanager.h"

DefaultRenderer::DefaultRenderer()
{

}

void DefaultRenderer::Start()
{
    VertexBuffer quad_vertex_buffer;

    quad_vertex_buffer.AddFloat3(float3(-0.5f, 0.5f, 0));
    quad_vertex_buffer.AddFloat2(float2(0.0f, 0.0f));

    quad_vertex_buffer.AddFloat3(float3(0.5f, 0.5f, 0));
    quad_vertex_buffer.AddFloat2(float2(1.0f, 0.0f));

    quad_vertex_buffer.AddFloat3(float3(0.5f, -0.5f, 0));
    quad_vertex_buffer.AddFloat2(float2(1.0f, 1.0f));

    quad_vertex_buffer.AddFloat3(float3(-0.5f, -0.5f, 0));
    quad_vertex_buffer.AddFloat2(float2(0.0f, 1.0f));

    uint indices[] =
    {
        0, 1, 3,
        1, 2, 3
    };

    const char* vertex_code =
    "#version 330 core\n \
    layout(location = 0) in vec3 position; \n \
    layout(location = 1) in vec2 uvs; \n \
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
        gl_Position = Projection * View * Model * vec4(vec3(position.x, position.y, z_pos), 1);\
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

    // VAO
    vao = RenderManager::Instance()->GenVertexArrayBuffer();
    RenderManager::Instance()->BindVertexArrayBuffer(vao);

    // VBO
    int vbo = RenderManager::Instance()->GenBuffer();
    RenderManager::Instance()->BindArrayBuffer(vbo);

    RenderManager::Instance()->LoadArrayToVRAM(quad_vertex_buffer.GetSize(), quad_vertex_buffer.GetBuffer(), GL_STATIC_DRAW);


    // Set info
    GLint posAttrib =  RenderManager::Instance()->GetVertexAttributeArray(program->GetID(), "position");
    RenderManager::Instance()->EnableVertexAttributeArray(posAttrib);
    RenderManager::Instance()->SetVertexAttributePointer(posAttrib, 3, 5, 0);

    GLint uvsAttrib =  RenderManager::Instance()->GetVertexAttributeArray(program->GetID(), "uvs");
    RenderManager::Instance()->EnableVertexAttributeArray(uvsAttrib);
    RenderManager::Instance()->SetVertexAttributePointer(uvsAttrib, 2, 5, 3);

    // VBIO
    uint vbio = RenderManager::Instance()->GenBuffer();
    RenderManager::Instance()->BindElementArrayBuffer(vbio);

    RenderManager::Instance()->LoadElementArrayToVRAM(sizeof(indices), &indices[0], GL_STATIC_DRAW);

    // Clear
    RenderManager::Instance()->UnbindVertexArrayBuffer();

    RenderManager::Instance()->DisableVertexAttributeArray(posAttrib);
    RenderManager::Instance()->DisableVertexAttributeArray(uvsAttrib);

    quad_vertex_buffer.Clear();
}

void DefaultRenderer::Render(const float4x4 &view, const float4x4 &projection)
{
    // Rendering test quad

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glDepthFunc(GL_LESS);

    program->UseProgram();

    RenderManager::Instance()->BindVertexArrayBuffer(vao);

    RenderManager::Instance()->SetUniformMatrix(program->GetID(), "View", view.ptr());
    RenderManager::Instance()->SetUniformMatrix(program->GetID(), "Projection", projection.ptr());

    float4 colour = float4(1, 1, 1, 1);

    float4x4 size_mat = float4x4::identity;

    size_mat = float4x4::FromTRS(float3::zero, Quat::identity, float3(100, 500, 1));

    float4x4 world_transform = float4x4::FromTRS(float3::zero, Quat::identity, float3(1, 2, 1));

    RenderManager::Instance()->SetUniformFloat(program->GetID(), "z_pos", 1);

    RenderManager::Instance()->SetUniformVec4(program->GetID(), "col", colour);
    RenderManager::Instance()->SetUniformInt(program->GetID(), "hasTexture", false);

    RenderManager::Instance()->SetUniformMatrix(program->GetID(), "Model", world_transform.Transposed().ptr());

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {

    }

    RenderManager::Instance()->UnbindVertexArrayBuffer();

    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}

void DefaultRenderer::CleanUp()
{
    ShaderManager::Instance()->DestroyShaderProgram(program);
}
