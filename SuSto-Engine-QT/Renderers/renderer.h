#ifndef RENDERER_H
#define RENDERER_H

#include "3rdParty/MathGeoLib/MathGeoLib.h"

class Mesh;
class RenderTarget;
class Camera3D;

class Renderer
{
public:
    Renderer() {};

    virtual void Start() {}
    virtual void Render(Camera3D* camera, const float4x4& view, const float4x4& projection, RenderTarget* target) {}
    virtual void CleanUp() {}
};

#endif // RENDERER_H
