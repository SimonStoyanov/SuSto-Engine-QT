#include "rendertarget.h"
#include "Managers/rendermanager.h"

RenderTarget::RenderTarget()
{

}

void RenderTarget::Start()
{
    Resize(float2(1280, 720));
}

void RenderTarget::CleanUp()
{

}

void RenderTarget::Resize(const float2 &new_size)
{
    RenderManager::Instance()->UseGL();

    if(new_size.x != size.x || new_size.y != size.y)
    {
        size = new_size;

        position_color_texture = RenderManager::Instance()->GenTexture();
        RenderManager::Instance()->BindTexture(position_color_texture);
        RenderManager::Instance()->LoadTextureToVRAM(position_color_texture, size.x, size.y, nullptr, GL_RGB8, GL_RGB, GL_FLOAT);

        normal_color_texture = RenderManager::Instance()->GenTexture();
        RenderManager::Instance()->BindTexture(normal_color_texture);
        RenderManager::Instance()->LoadTextureToVRAM(normal_color_texture, size.x, size.y, nullptr, GL_RGB8, GL_RGBA, GL_FLOAT);

        color_plus_specular_color_texture = RenderManager::Instance()->GenTexture();
        RenderManager::Instance()->BindTexture(normal_color_texture);
        RenderManager::Instance()->LoadTextureToVRAM(color_plus_specular_color_texture, size.x, size.y, nullptr, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);

        depth_texture = RenderManager::Instance()->GenTexture();
        RenderManager::Instance()->BindTexture(depth_texture);
        RenderManager::Instance()->LoadTextureToVRAM(depth_texture, size.x, size.y, nullptr, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_FLOAT);

        fbo_texture = RenderManager::Instance()->GenFrameBuffer();
        RenderManager::Instance()->BindFrameBuffer(fbo_texture);
        RenderManager::Instance()->SetFrameBufferTexture2D(GL_TEXTURE_2D, GL_COLOR_ATTACHMENT0, position_color_texture);
        RenderManager::Instance()->SetFrameBufferTexture2D(GL_TEXTURE_2D, GL_COLOR_ATTACHMENT1, normal_color_texture);
        RenderManager::Instance()->SetFrameBufferTexture2D(GL_TEXTURE_2D, GL_COLOR_ATTACHMENT2, color_plus_specular_color_texture);
        RenderManager::Instance()->SetFrameBufferTexture2D(GL_TEXTURE_2D, GL_DEPTH_ATTACHMENT, depth_texture);

        RenderManager::Instance()->DrawBuffer(GL_COLOR_ATTACHMENT0);

        CheckStatus();
    }
}

void RenderTarget::Bind()
{
    RenderManager::Instance()->BindFrameBuffer(fbo_texture);
}

void RenderTarget::UnBind()
{
    RenderManager::Instance()->BindFrameBuffer(0);
}

int RenderTarget::GetPositionColorTextureId() const
{
    return position_color_texture;
}

void RenderTarget::CheckStatus()
{
    GLenum status = RenderManager::Instance()->CheckFrameBufferStatus();

    switch(status)
    {
    case GL_FRAMEBUFFER_COMPLETE: // Everything's OK
    {
        break;
    }
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
    {
        SPOOKYLOG("Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
        break;
    }
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
    {
        SPOOKYLOG("Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
        break;
    }
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
    {
        SPOOKYLOG("Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");
        break;
    }
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
    {
        SPOOKYLOG("Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER");
        break;
    }
    case GL_FRAMEBUFFER_UNSUPPORTED:
    {
        SPOOKYLOG("Framebuffer ERROR: GL_FRAMEBUFFER_UNSUPPORTED");
        break;
    }
    default:
    {
        SPOOKYLOG("Framebuffer ERROR: Unknown ERROR");
        break;
    }
    }
}