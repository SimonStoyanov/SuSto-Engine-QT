#ifndef DEFAULTRENDERER_H
#define DEFAULTRENDERER_H

#include "Renderers/Renderer.h"

class ShaderProgram;
class Mesh;

class GeometryRenderer : public Renderer
{
public:
    GeometryRenderer();

    void Start();
    void Render(Camera3D* camera, const float4x4& view, const float4x4& projection, RenderTarget* target);
    void CleanUp();

private:
    ShaderProgram* program = nullptr;
};

#endif // DEFAULTRENDERER_H
