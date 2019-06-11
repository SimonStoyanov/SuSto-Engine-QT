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
    void Render(Camera3D* camera, const float4x4& view, const float4x4& projection, RenderTarget* target);
    void CleanUp();

private:
    ShaderProgram* program = nullptr;

    Mesh* plane_mesh = nullptr;
};

#endif // RENDERTARGETRENDERER_H

