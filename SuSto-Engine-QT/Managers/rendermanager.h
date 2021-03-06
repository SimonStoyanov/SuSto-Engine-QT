#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <vector>
#include "drawingwidget.h"
#include <QOpenGLFunctions_3_3_Core>
#include "3rdParty/MathGeoLib/MathGeoLib.h"

class RendererWidget;

class RenderManager
{
    friend class AppManager;

private:
    RenderManager();
    void operator delete(void *) {}

public:
    static RenderManager* Instance()
    {
        if(instance == nullptr)
        {
            instance = new RenderManager();
        }

        return instance;
    }

    static void DestroyInstance()
    {
        if(instance != nullptr)
        {
            instance->CleanUp();

            delete instance;

            instance = nullptr;
        }
    }

public:
    void SetGL(RendererWidget* widget);

    void UseGL();

    void Clear();

    std::string GetErrorString(GLenum name) const;

    // OpenGl control -----------------------------------------

    void SwapWindowBuffers();

    void SetViewport(uint start_x, uint start_y, uint width, uint height);
    void GetViewport(uint& start_x, uint& start_y, uint& width, uint& height);

    uint GenBuffer() const;
    void UnloadBuffer(uint& id);

    void BindArrayBuffer(uint id) const;
    void BindElementArrayBuffer(uint id) const;

    void UnbindArrayBuffer() const;
    void UnbindElementArrayBuffer() const;

    uint GenTexture() const;
    void SetActiveTexture(uint target);
    void BindTexture(uint id) const;
    void BindTexture(uint target, uint id) const;
    void UnbindTexture() const;
    void UnbindTexture(uint target) const;
    void DeleteTexture(uint& id) const;

    uint GenRenderBuffer() const;
    void BindRenderBuffer(uint id) const;
    void UnbindRenderBuffer() const;

    void Set2DMultisample(uint samples, uint width, uint height);
    void SetFrameBufferTexture2D(uint target, uint id);
    void SetFrameBufferTexture2D(uint target, uint attachment, uint id);
    void RenderStorageMultisample(uint samples, uint width, uint height);

    void LoadArrayToVRAM(uint size, const float* values, GLenum type = GL_STATIC_DRAW) const;
    void LoadElementArrayToVRAM(uint size, uint* values, GLenum type = GL_STATIC_DRAW) const;
    uint LoadTextureToVRAM(uint w, uint h, GLubyte* tex_data, GLint format) const;
    uint LoadTextureToVRAM(uint w, uint h, GLubyte* tex_data, GLint internal_format, GLint format, GLint type) const;
    void LoadTextureToVRAM(uint texture_id, uint w, uint h, GLubyte* tex_data, GLint internal_format, GLint format, GLint type);

    void DrawElements(GLenum mode, uint elements_count);

    // --------------------------------------------------------

    // Shaders ------------------------------------------------

    uint GenVertexArrayBuffer() const;
    void BindVertexArrayBuffer(uint id) const;
    void UnbindVertexArrayBuffer() const;

    uint GenFrameBuffer() const;
    void BindFrameBuffer(uint id) const;
    void BindFrameBuffer(uint target, uint id) const;
    void BlitFrameBuffer(uint x, uint y, uint w, uint h) const;
    void RenderFrameBuffer(uint id) const;
    void UnbindFrameBuffer() const;
    void UnbindFrameBuffer(uint target) const;
    uint CheckFrameBufferStatus();
    void DeleteFrameBuffer(uint id);
    void DrawBuffer(uint mode);
    void DrawBuffers(uint ammount, uint* modes);

    uint CreateVertexShader(const char* source, std::string& compilation_error_msg);
    uint CreateFragmentShader(const char* source, std::string& compilation_error_msg);
    uint CreateGeometryShader(const char* source, std::string& compilation_error_msg);
    void DeleteShader(uint shader_id);

    void BindAttributeLocation(uint program_id, uint index, const char* name);

    GLint GetVertexAttributeArray(uint program, const char* name);
    void EnableVertexAttributeArray(uint id);
    void DisableVertexAttributeArray(uint id);
    void SetVertexAttributePointer(uint id, uint element_size, uint elements_gap, uint infogap);

    uint GetAttributesCount(uint program);
    void GetAttributesInfo(uint program, uint index, std::string& name, GLenum& type);

    void SetUniformMatrix(uint program, const char* name, const float* data);
    void SetUniformFloat(uint program, const char* name, float data);
    void SetUniformInt(uint program, const char* name, int data);
    void SetUniformBool(uint program, const char* name, bool data);
    void SetUniformVec3(uint program, const char* name, const float3& data);
    void SetUniformVec4(uint program, const char* name, const float4& data);

    void SetArrayUniformMatrix(uint program, const char* array_name, const char* name,int index, const float* data);
    void SetArrayUniformFloat(uint program, const char* array_name, const char* name,int index, float data);
    void SetArrayUniformInt(uint program, const char* array_name, const char* name, int index, int data);
    void SetArrayUniformBool(uint program, const char* array_name, const char* name, int index, bool data);
    void SetArrayUniformVec3(uint program, const char* array_name, const char* name, int index, const float3& data);
    void SetArrayUniformVec4(uint program, const char* array_name, const char* name, int index, const float4& data);

    uint GetUniformsCount(uint program);
    void GetUniformInfo(uint program, uint index, std::string& name, GLenum& type);

    uint CreateShaderProgram();
    void UseShaderProgram(uint id);
    void AttachShaderToProgram(uint program, uint shader_id);
    bool LinkProgram(uint program, std::string& link_error);
    void DeleteProgram(uint program);

    // --------------------------------------------------------

private:
    void Start();
    void Update();
    void CleanUp();


private:
    static RenderManager* instance;

    RendererWidget* gl = nullptr;

};

#endif // RENDERMANAGER_H
