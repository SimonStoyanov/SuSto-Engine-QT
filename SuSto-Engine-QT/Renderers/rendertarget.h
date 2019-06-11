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

    int GetPositionColorTextureId() const;
    int GetNormalColorTextureId() const;
    int GetColorPlusSpecularColorTextureId() const;
    int GetAmbientLightTextureId() const;
    int GetLightTextureId() const;
    int GetDepthTextureId() const;

private:
    void CheckStatus();

private:
    float2 size = float2::zero;

    uint position_color_texture = 0;
    uint normal_color_texture = 0;
    uint color_plus_specular_color_texture = 0;
    uint ambient_light_texture = 0;
    uint light_texture = 0;
    uint depth_texture = 0;

    uint fbo_texture = 0;
};

#endif // RENDERTARGET_H
