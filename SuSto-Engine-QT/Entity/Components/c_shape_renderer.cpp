#include "c_shape_renderer.h".h"
#include "entity.h"
#include "component.h"
#include "Managers/shapemanager.h"

C_ShapeRenderer::C_ShapeRenderer(Entity* owner) : Component(ComponentType::COMPONENT_SHAPE_RENDERER, owner)
{

}

void C_ShapeRenderer::Start()
{

}

void C_ShapeRenderer::CleanUp()
{
    ShapeManager::Instance()->DestroyShape(curr_shape);
}

void C_ShapeRenderer::CreateShape(ShapeType type)
{
    if(curr_shape != nullptr)
    {
        ShapeManager::Instance()->DestroyShape(curr_shape);
    }

   curr_shape = ShapeManager::Instance()->CreateShape(type);
}
