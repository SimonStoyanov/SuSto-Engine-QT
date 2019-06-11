#ifndef AMBIENTLIGHTRENDERER_H
#define AMBIENTLIGHTRENDERER_H

#include "renderer.h"

class ShaderProgram;

class AmbientLightRenderer : public Renderer
{
public:
    AmbientLightRenderer();

    void Start();
    void Render(Camera3D* camera, const float4x4& view, const float4x4& projection, RenderTarget* target);
    void CleanUp();

private:
    ShaderProgram* program = nullptr;

    Mesh* plane_mesh = nullptr;
};

#endif // AMBIENTLIGHTRENDERER_H
