#include "shapemanager.h"

ShapeManager* ShapeManager::instance = nullptr;

ShapeManager::ShapeManager()
{

}

void ShapeManager::Start()
{

}

void ShapeManager::CleanUp()
{

}

Shape* ShapeManager::CreateShape(ShapeType type)
{
    Shape* ret = nullptr;

    switch (type)
    {
    case ShapeType::SHAPE_CIRCLE:
    {
        break;
    }

    case ShapeType::SHAPE_QUAD:
    {
        break;
    }

    }

    if(ret != nullptr)
    {
        shapes.push_back(ret);
    }

    return ret;
}

void ShapeManager::DestroyShape(Shape*& sh)
{
    if(sh != nullptr)
    {
        for(std::vector<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it)
        {
            if((*it) == sh)
            {
                shapes.erase(it);
                break;
            }
        }

        delete sh;
        sh = nullptr;
    }
}

std::vector<Shape *> ShapeManager::GetShapes() const
{
    return shapes;
}

