#include "shapemanager.h"
#include "Shapes/shapecircle.h"

ShapeManager* ShapeManager::instance = nullptr;

ShapeManager::ShapeManager()
{

}

void ShapeManager::Start()
{
    AddShapeType(ShapeType::SHAPE_CIRCLE, "Circle");
    AddShapeType(ShapeType::SHAPE_QUAD, "Quad");
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
        ret = new ShapeCircle();
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

void ShapeManager::AddShapeType(ShapeType type, const std::string &name)
{
    shapes_types[type] = name;
}

ShapeType ShapeManager::GetShapeTypeByShapeName(const std::string &shape_name) const
{
    ShapeType ret = ShapeType::SHAPE_NULL;

    for(std::map<ShapeType, std::string>::const_iterator it = shapes_types.begin(); it != shapes_types.end(); ++it)
    {
        if((*it).second.compare(shape_name) == 0)
        {
            ret = (*it).first;
            break;
        }
    }

    return ret;
}

std::map<ShapeType, std::string> ShapeManager::GetAllShapeTypes()
{
    return shapes_types;
}

