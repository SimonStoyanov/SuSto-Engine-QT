#ifndef RENDERTARGETRENDERER_H
#define RENDERTARGETRENDERER_H

#include "Renderers/Renderer.h"

class ShaderProgram;
class Mesh;
class RenderTarget;

class RenderTargetRenderer : public Renderer
{
public:
    RenderTargetRenderer();

    void Start();
    void Render(const float4x4& view, const float4x4& projection);
    void CleanUp();

    void SetTarget(RenderTarget* target);

private:
    ShaderProgram* program = nullptr;
    RenderTarget* render_target = nullptr;

    Mesh* plane_mesh = nullptr;
};

#endif // RENDERTARGETRENDERER_H

