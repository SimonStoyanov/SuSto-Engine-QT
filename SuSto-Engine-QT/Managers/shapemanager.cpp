#include "shapemanager.h"
#include "Shapes/shapecircle.h"
#include "Shapes/shapequad.h"

ShapeManager* ShapeManager::instance = nullptr;

ShapeManager::ShapeManager()
{

}

void ShapeManager::SetDrawingWidget(DrawingWidget *set)
{
    drawing_widget = set;
}

void ShapeManager::RepaintDrawingWidget()
{
    if(drawing_widget != nullptr)
        drawing_widget->update();
}

void ShapeManager::Start()
{
    AddShapeType(ShapeType::SHAPE_CIRCLE, "Circle");
    AddShapeType(ShapeType::SHAPE_QUAD, "Quad");

    AddStrokeStyleType(Qt::PenStyle::SolidLine, "SolidLine");
    AddStrokeStyleType(Qt::PenStyle::DotLine, "DotLine");
    AddStrokeStyleType(Qt::PenStyle::DashLine, "DashLine");
    AddStrokeStyleType(Qt::PenStyle::DashDotLine, "DashDotLine");
    AddStrokeStyleType(Qt::PenStyle::DashDotDotLine, "DashDotDotLine");
    AddStrokeStyleType(Qt::PenStyle::NoPen, "NoPen");
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
        ret = new ShapeQuad();
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

void ShapeManager::AddStrokeStyleType(Qt::PenStyle type, const std::string &name)
{
    stroke_styles[type] = name;
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

Qt::PenStyle ShapeManager::GetStrokeStyleTypeByStrokeStyleName(const std::string &stroke_style_name) const
{
    Qt::PenStyle ret = Qt::PenStyle::NoPen;

    for(std::map<Qt::PenStyle, std::string>::const_iterator it = stroke_styles.begin(); it != stroke_styles.end(); ++it)
    {
        if((*it).second.compare(stroke_style_name) == 0)
        {
            ret = (*it).first;
            break;
        }
    }

    return ret;
}

std::map<Qt::PenStyle, std::string> ShapeManager::GetAllStrokeStyleTypes()
{
    return stroke_styles;
}

