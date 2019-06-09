#ifndef RENDERER_H
#define RENDERER_H

#include "3rdParty/MathGeoLib/MathGeoLib.h"

class Mesh;
class RenderTarget;

class Renderer
{
public:
    Renderer() {};

    virtual void Start() {}
    virtual void Render(const float4x4& view, const float4x4& projection) {}
    virtual void CleanUp() {}
};

#endif // RENDERER_H
