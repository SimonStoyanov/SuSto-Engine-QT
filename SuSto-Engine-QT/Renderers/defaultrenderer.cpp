#include "defaultrenderer.h"
#include "Renderers/vertexbuffer.h"
#include "Managers/shadermanager.h"

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

    int indices[] =
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

}

void DefaultRenderer::Render(const float4x4 &view, const float4x4 &projection)
{

}

void DefaultRenderer::CleanUp()
{

}
