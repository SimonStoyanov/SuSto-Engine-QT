#include "rendermanager.h"
#include "globals.h"
#include <QSurfaceFormat>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "rendererwidget.h"
#include "Managers/scenerenderermanager.h"

#pragma comment(lib, "OpenGL32.lib")

RenderManager* RenderManager::instance = nullptr;

RenderManager::RenderManager()
{

}

void RenderManager::SetGL(RendererWidget *widget)
{
    gl = widget;

    if(gl != nullptr)
    {
        SPOOKYLOG("OpenGL initialized");

        SceneRendererManager::Instance()->StartRenderers();
    }
}

void RenderManager::Start()
{
    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setMinorVersion(3);
    format.setMajorVersion(3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setRedBufferSize(8);
    format.setGreenBufferSize(8);
    format.setBlueBufferSize(8);
    format.setAlphaBufferSize(8);
    format.setSwapBehavior(QSurfaceFormat::SwapBehavior::DoubleBuffer);
    QSurfaceFormat::setDefaultFormat(format);
}

void RenderManager::CleanUp()
{

}

std::string RenderManager::GetErrorString(GLenum name) const
{
    const char* error = (const char*)glGetString(name);

    return error;
}

void RenderManager::SwapWindowBuffers()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderManager::SetViewport(uint start_x, uint start_y, uint width, uint height)
{
    glViewport(start_x, start_y, width, height);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error setting viewport: " + GetErrorString(error));
    }
}

void RenderManager::GetViewport(uint &start_x, uint &start_y, uint &width, uint &height)
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    start_x = viewport[0];
    start_y = viewport[1];
    width = viewport[2];
    height = viewport[3];

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error getting viewport: " + GetErrorString(error));
    }
}

uint RenderManager::GenBuffer() const
{
    uint ret = 0;

    gl->glGenBuffers(1, (GLuint*)&ret);

    return ret;
}

void RenderManager::UnloadBuffer(uint &id)
{
    if(id > 0)
        gl->glDeleteBuffers(1, &id);
}

void RenderManager::BindArrayBuffer(uint id) const
{
    gl->glBindBuffer(GL_ARRAY_BUFFER, id);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error bind array buffer: " + GetErrorString(error));
    }
}

void RenderManager::BindElementArrayBuffer(uint id) const
{
    gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error bind element array buffer: " + GetErrorString(error));
    }
}

void RenderManager::UnbindArrayBuffer() const
{
    gl->glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error unbind array buffer: " + GetErrorString(error));
    }
}

void RenderManager::UnbindElementArrayBuffer() const
{
    gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error unbind element array buffer: " + GetErrorString(error));
    }
}

uint RenderManager::GenTexture() const
{
    uint ret = 0;

    gl->glGenTextures(1, &ret);

    return ret;
}

void RenderManager::BindTexture(uint id) const
{
    BindTexture(GL_TEXTURE_2D, id);
}

void RenderManager::BindTexture(uint target, uint id) const
{
    gl->glBindTexture((GLenum)target, id);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error bind texture: " + GetErrorString(error));
    }
}

void RenderManager::UnbindTexture() const
{
    UnbindTexture(GL_TEXTURE_2D);
}

void RenderManager::UnbindTexture(uint target) const
{
    gl->glBindTexture(target, 0);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error unbind texture: " + GetErrorString(error));
    }
}

void RenderManager::DeleteTexture(uint &id) const
{
    if (id > 0)
    {
        gl->glDeleteTextures(1, &id);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            SPOOKYLOG("Error deleting texture: " + GetErrorString(error));
        }
    }
}

uint RenderManager::GenRenderBuffer() const
{
    uint ret = 0;

    gl->glGenRenderbuffers(1, &ret);

    return ret;
}

void RenderManager::BindRenderBuffer(uint id) const
{
    gl->glBindRenderbuffer(GL_RENDERBUFFER, id);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error binding render buffer: " + GetErrorString(error));
    }
}

void RenderManager::UnbindRenderBuffer() const
{
    gl->glBindRenderbuffer(GL_RENDERBUFFER, 0);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error unbind render buffer: " + GetErrorString(error));
    }
}

void RenderManager::Set2DMultisample(uint samples, uint width, uint height)
{
    gl->glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGBA, width, height, GL_TRUE);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error setting 2D multisample texture: " + GetErrorString(error));
    }
}

void RenderManager::SetFrameBufferTexture2D(uint target, uint id)
{
    gl->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, target, id, 0);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error setting frame buffer texture2D: " + GetErrorString(error));
    }
}

void RenderManager::RenderStorageMultisample(uint samples, uint width, uint height)
{
    gl->glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, width, height);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error rendering storage multisample: " + GetErrorString(error));
    }
}

void RenderManager::LoadArrayToVRAM(uint size, const float *values, GLenum type) const
{
    gl->glBufferData(GL_ARRAY_BUFFER, size, values, type);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error load array to vram: " + GetErrorString(error));
    }
}

void RenderManager::LoadElementArrayToVRAM(uint size, uint *values, GLenum type) const
{
    gl->glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, values, type);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error load array to vram: " + GetErrorString(error));
    }
}

uint RenderManager::LoadTextureToVRAM(uint w, uint h, GLubyte *tex_data, GLint format) const
{
    uint buff_id = 0;

    gl->glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    gl->glGenTextures(1, &buff_id);
    gl->glBindTexture(GL_TEXTURE_2D, buff_id);
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl->glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, tex_data);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error load texture to vram: " + GetErrorString(error));
    }

    return buff_id;
}

uint RenderManager::GenVertexArrayBuffer() const
{
    uint ret = 0;

    gl->glGenVertexArrays(1, (GLuint*)&ret);

    return ret;
}

void RenderManager::BindVertexArrayBuffer(uint id) const
{
    gl->glBindVertexArray(id);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error bind vertex array buffer: " + GetErrorString(error));
    }
}

void RenderManager::UnbindVertexArrayBuffer() const
{
    gl->glBindVertexArray(0);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error unbind array buffer: " + GetErrorString(error));
    }
}

uint RenderManager::GenFrameBuffer() const
{
    uint ret = 0;

    gl->glGenFramebuffers(1, (GLuint*)&ret);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error generating frame buffer: " + GetErrorString(error));
    }

    return ret;
}

void RenderManager::BindFrameBuffer(uint id) const
{
    BindFrameBuffer(GL_FRAMEBUFFER, id);
}

void RenderManager::BindFrameBuffer(uint target, uint id) const
{
    gl->glBindFramebuffer(target, id);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error binding frame buffer: " + GetErrorString(error));
    }
}

void RenderManager::BlitFrameBuffer(uint x, uint y, uint w, uint h) const
{
    gl->glBlitFramebuffer(x, y, w, h,  // src rect
        x, y, w, h,  // dst rect
        GL_COLOR_BUFFER_BIT, // buffer mask
        GL_NEAREST); // scale filter

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error bliting frame buffer: " + GetErrorString(error));
    }
}

void RenderManager::RenderFrameBuffer(uint id) const
{
    gl->glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, id);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error rendering frame buffer: " + GetErrorString(error));
    }
}

void RenderManager::UnbindFrameBuffer() const
{
    UnbindFrameBuffer(GL_FRAMEBUFFER);
}

void RenderManager::UnbindFrameBuffer(uint target) const
{
    gl->glBindFramebuffer(target, 0);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error unbinding frame buffer: " + GetErrorString(error));
    }
}

uint RenderManager::CheckFrameBufferStatus()
{
    uint ret = 0;

    ret = gl->glCheckFramebufferStatus(GL_FRAMEBUFFER);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error checking frame buffer status: " + GetErrorString(error));
    }

    return ret;
}

void RenderManager::DeleteFrameBuffer(uint &id)
{
    if (id > 0)
    {
        gl->glDeleteFramebuffers(1, &id);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            SPOOKYLOG("Error deleting frame buffer: " + GetErrorString(error));
        }
    }
}

uint RenderManager::CreateVertexShader(const char *source, std::string &compilation_error_msg)
{
    GLuint vertexShader = 0;

    vertexShader = gl->glCreateShader(GL_VERTEX_SHADER);  

    gl->glShaderSource(vertexShader, 1, &source, NULL);
    gl->glCompileShader(vertexShader);

    GLint success;
    GLchar infoLog[512];
    gl->glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (success == 0)
    {
        gl->glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);

        SPOOKYLOG("Vertex shader compilation error: " + std::string(infoLog));

        gl->glDeleteShader(vertexShader);

        compilation_error_msg = infoLog;
        vertexShader = 0;
    }

    return vertexShader;
}

uint RenderManager::CreateFragmentShader(const char *source, std::string &compilation_error_msg)
{
    GLuint fragmentShader = 0;

    fragmentShader = gl->glCreateShader(GL_FRAGMENT_SHADER);

    gl->glShaderSource(fragmentShader, 1, &source, NULL);
    gl->glCompileShader(fragmentShader);

    GLint success;
    GLchar infoLog[512];
    gl->glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (success == 0)
    {
        gl->glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);

        SPOOKYLOG("Fragment shader compilation error: " + std::string(infoLog));

        gl->glDeleteShader(fragmentShader);

        compilation_error_msg = infoLog;
        fragmentShader = 0;
    }

    return fragmentShader;
}

uint RenderManager::CreateGeometryShader(const char *source, std::string &compilation_error_msg)
{
    GLuint geometryShader = 0;

    geometryShader = gl->glCreateShader(GL_GEOMETRY_SHADER);

    gl->glShaderSource(geometryShader, 1, &source, NULL);
    gl->glCompileShader(geometryShader);

    GLint success;
    GLchar infoLog[512];
    gl->glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);

    if (success == 0)
    {
        gl->glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);

        SPOOKYLOG("Geometry shader compilation error: " + std::string(infoLog));

        gl->glDeleteShader(geometryShader);

        compilation_error_msg = infoLog;
        geometryShader = 0;
    }

    return geometryShader;
}

void RenderManager::DeleteShader(uint shader_id)
{
    if (shader_id > 0)
    {
        gl->glDeleteShader(shader_id);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            SPOOKYLOG("Error deleting shader: " + GetErrorString(error));
        }
    }
}

void RenderManager::BindAttributeLocation(uint program_id, uint index, const char *name)
{
    gl->glBindAttribLocation(program_id, index, name);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error binding attribute locaiton on shader: " + GetErrorString(error));
    }
}

GLint RenderManager::GetVertexAttributeArray(uint program, const char *name)
{
    GLint ret = -1;

    ret = gl->glGetAttribLocation(program, name);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error getting vertex attribute array: " + GetErrorString(error));
    }

    return ret;
}

void RenderManager::EnableVertexAttributeArray(uint id)
{
    gl->glEnableVertexAttribArray(id);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error enabling vertex attribute array: " + GetErrorString(error));
    }
}

void RenderManager::DisableVertexAttributeArray(uint id)
{
    gl->glDisableVertexAttribArray(id);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error disabling vertex attribute array: " + GetErrorString(error));
    }
}

void RenderManager::SetVertexAttributePointer(uint id, uint element_size, uint elements_gap, uint infogap)
{
    gl->glVertexAttribPointer(id, element_size, GL_FLOAT, GL_FALSE, elements_gap * sizeof(GLfloat), (void*)(infogap * sizeof(GLfloat)));

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error Setting vertex attribute pointer: " + GetErrorString(error));
    }
}

uint RenderManager::GetAttributesCount(uint program)
{
    uint ret = 0;

    GLint count = 0;
    gl->glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &count);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error getting attributes count on program " + std::to_string(program) + ": " + GetErrorString(error));
    }

    ret = count;

    return ret;
}

void RenderManager::GetAttributesInfo(uint program, uint index, std::string &name, GLenum &type)
{
    const GLsizei bufSize = 100;
    GLchar c_name[bufSize];
    GLsizei length;
    GLint size;

    gl->glGetActiveAttrib(program, (GLuint)index, bufSize, &length, &size, &type, c_name);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
         SPOOKYLOG("Error getting attribute info on program " + std::to_string(program) + ": " + GetErrorString(error));
    }
}

void RenderManager::SetUniformMatrix(uint program, const char *name, const float *data)
{
    GLint modelLoc = gl->glGetUniformLocation(program, name);

    if (modelLoc != -1)
        gl->glUniformMatrix4fv(modelLoc, 1, GL_FALSE, data);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error setting uniform matrix " + std::to_string(program) + ": " + GetErrorString(error));
    }
}

void RenderManager::SetUniformFloat(uint program, const char *name, float data)
{
    GLint modelLoc = gl->glGetUniformLocation(program, name);

    if (modelLoc != -1)
        gl->glUniform1f(modelLoc, data);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error setting uniform float " + std::to_string(program) + ": " + GetErrorString(error));
    }
}

void RenderManager::SetUniformInt(uint program, const char *name, int data)
{
    GLint modelLoc = gl->glGetUniformLocation(program, name);

    if (modelLoc != -1)
        gl->glUniform1i(modelLoc, data);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error setting uniform int " + std::to_string(program) + ": " + GetErrorString(error));
    }
}

void RenderManager::SetUniformBool(uint program, const char *name, bool data)
{
    GLint modelLoc = gl->glGetUniformLocation(program, name);

    if (modelLoc != -1)
        gl->glUniform1i(modelLoc, data);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error setting uniform bool " + std::to_string(program) + ": " + GetErrorString(error));
    }
}

void RenderManager::SetUniformVec3(uint program, const char *name, const float3 &data)
{
    GLint modelLoc = gl->glGetUniformLocation(program, name);

    if (modelLoc != -1)
        gl->glUniform3f(modelLoc, data.x, data.y, data.z);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error setting uniform vec3 " + std::to_string(program) + ": " + GetErrorString(error));
    }
}

void RenderManager::SetUniformVec4(uint program, const char *name, const float4 &data)
{
    GLint modelLoc = gl->glGetUniformLocation(program, name);

    if (modelLoc != -1)
        gl->glUniform4f(modelLoc, data.x, data.y, data.w, data.z);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error setting uniform vec4 " + std::to_string(program) + ": " + GetErrorString(error));
    }
}

uint RenderManager::GetUniformsCount(uint program)
{
    uint ret = 0;

    GLint count = 0;
    gl->glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error getting uniforms count on program " + std::to_string(program) + ": " + GetErrorString(error));
    }

    ret = count;

    return ret;
}

void RenderManager::GetUniformInfo(uint program, uint index, std::string &name, GLenum &type)
{
    const GLsizei bufSize = 100;
    GLchar c_name[bufSize];
    GLsizei length;
    GLint size;

    gl->glGetActiveUniform(program, (GLuint)index, bufSize, &length, &size, &type, c_name);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error getting uniforms info on program " + std::to_string(program) + ": " + GetErrorString(error));
    }

    name = c_name;
}

uint RenderManager::CreateShaderProgram()
{
    uint ret = gl->glCreateProgram();

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error creating shader program");
    }

    return ret;
}

void RenderManager::UseShaderProgram(uint id)
{
    gl->glUseProgram(id);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        SPOOKYLOG("Error using shader program " + std::to_string(id) + ": " + GetErrorString(error));
    }
}

void RenderManager::AttachShaderToProgram(uint program, uint shader)
{
    if (program > 0 && shader > 0)
    {
        gl->glAttachShader(program, shader);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            SPOOKYLOG("Error attaching shader to program " + std::to_string(program) + ": " + GetErrorString(error));
        }
    }
}

bool RenderManager::LinkProgram(uint program, std::string &link_error)
{
    bool ret = false;

    if (program != 0)
    {
        gl->glLinkProgram(program);

        GLint success;
        GLint valid;
        gl->glGetProgramiv(program, GL_LINK_STATUS, &success);
        gl->glGetProgramiv(program, GL_VALIDATE_STATUS, &valid);

        ret = true;

        if (!success || !valid)
        {
            GLchar infoLog[512];
            gl->glGetProgramInfoLog(program, 512, NULL, infoLog);

            SPOOKYLOG("Error linking program: " + std::string(infoLog));

            link_error = infoLog;

            ret = false;
        }
    }

    return ret;
}

void RenderManager::DeleteProgram(uint program)
{
    if (program > 0)
    {
        gl->glDeleteProgram(program);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            SPOOKYLOG("Error deleting shader program " + std::to_string(program) + ": " + GetErrorString(error));
        }
    }
}




