#include "rendermanager.h"
#include "globals.h"
#include <QSurfaceFormat>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "rendererwidget.h"

#pragma comment(lib, "OpenGL32.lib")

RenderManager* RenderManager::instance = nullptr;

RenderManager::RenderManager()
{

}

void RenderManager::SetGL(RendererWidget *widget)
{
    gl = widget;
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




