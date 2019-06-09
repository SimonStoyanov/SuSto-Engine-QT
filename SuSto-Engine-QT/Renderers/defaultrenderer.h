#ifndef DEFAULTRENDERER_H
#define DEFAULTRENDERER_H

#include "Renderers/Renderer.h"

class ShaderProgram;
class Mesh;

class DefaultRenderer : public Renderer
{
public:
    DefaultRenderer();

    void Start();
    void Render(const float4x4& view, const float4x4& projection);
    void CleanUp();

private:
    ShaderProgram* program = nullptr;
};

#endif // DEFAULTRENDERER_H
