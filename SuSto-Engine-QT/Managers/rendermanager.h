#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <vector>
#include "drawingwidget.h"
#include <QOpenGLFunctions_3_3_Core>

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
    void RenderStorageMultisample(uint samples, uint width, uint height);

    void LoadArrayToVRAM(uint size, const float* values, GLenum type = GL_STATIC_DRAW) const;
    void LoadElementArrayToVRAM(uint size, uint* values, GLenum type = GL_STATIC_DRAW) const;
    uint LoadTextureToVRAM(uint w, uint h, GLubyte* tex_data, GLint format) const;

    /*
    void UpdateVRAMArray(uint size, const float* values, GLenum type = GL_STATIC_DRAW) const;

    void PushMatrix();
    void PopMatrix();
    void MultMatrix(float* matrix);
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
    uint CheckFrameBufferStatus();
    void DeleteFrameBuffer(uint& id);

    uint CreateVertexShader(const char* source, std::string& compilation_error_msg = std::string());
    uint CreateFragmentShader(const char* source, std::string& compilation_error_msg = std::string());
    uint CreateGeometryShader(const char* source, std::string& compilation_error_msg = std::string());
    void DeleteShader(uint shader_id);

    uint GetProgramBinary(uint program_id, uint buff_size, char* buff) const;
    int GetProgramSize(uint program_id) const;
    void LoadProgramFromBinary(uint program_id, uint buff_size, const char* buff);

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

    uint GetUniformsCount(uint program);
    void GetUniformInfo(uint program, uint index, std::string& name, GLenum& type);

    uint CreateShaderProgram();
    void UseShaderProgram(uint id);
    void AttachShaderToProgram(uint program_id, uint shader_id);
    bool LinkProgram(uint program_id, std::string& link_error = std::string());
    void DeleteProgram(uint program_id);*/
    // --------------------------------------------------------

private:
    void Start();
    void CleanUp();


private:
    static RenderManager* instance;

    RendererWidget* gl = nullptr;

};

#endif // RENDERMANAGER_H
