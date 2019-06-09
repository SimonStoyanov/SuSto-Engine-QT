#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#include "3rdParty/MathGeoLib/Math/float2.h"
#include "globals.h"

class RenderTarget
{
public:
    RenderTarget();

    void Start();
    void CleanUp();

    void Resize(const float2& new_size);

    void Bind();
    void UnBind();

    int GetColorTextureId() const;

private:
    void CheckStatus();

private:
    float2 size = float2::zero;

    uint color_texture = 0;
    uint depth_texture = 0;

    uint fbo_texture = 0;
};

#endif // RENDERTARGET_H
