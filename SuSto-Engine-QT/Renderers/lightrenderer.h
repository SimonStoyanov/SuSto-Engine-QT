#ifndef LIGHTRENDERER_H
#define LIGHTRENDERER_H

#include "renderer.h"

class ShaderProgram;

class LightRenderer : public Renderer
{
public:
    LightRenderer();

    void Start();
    void Render(Camera3D* camera, const float4x4& view, const float4x4& projection, RenderTarget* target);
    void CleanUp();

private:
    void RenderDirectionals(Camera3D* camera, const float4x4& view, const float4x4& projection, RenderTarget* target);

private:
    ShaderProgram* program = nullptr;

    Mesh* plane_mesh = nullptr;
    Mesh* sphere_mesh = nullptr;
};

#endif // LIGHTRENDERER_H
