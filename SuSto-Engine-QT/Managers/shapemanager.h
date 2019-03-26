#ifndef SHAPEMANAGER_H
#define SHAPEMANAGER_H

#include <vector>
#include "drawingwidget.h"

#include "Shapes/shape.h"

class ShapeManager
{
    ShapeManager();
    void operator delete(void *) {}

public:
    static ShapeManager* Instance()
    {
        if(instance == nullptr)
        {
            instance = new ShapeManager();

            instance->Start();
        }

        return instance;
    }

    static void DestroyInstance()
    {
        if(instance != nullptr)
        {
            instance->CleanUp();

            delete instance;

            instance = nullptr;
        }
    }

    void SetDrawingWidget(DrawingWidget* set);
    void RepaintDrawingWidget();

    Shape* CreateShape(ShapeType type);
    void DestroyShape(Shape*& sh);
    std::vector<Shape*> GetShapes() const;

    ShapeType GetShapeTypeByShapeName(const std::string& shape_name) const;
    std::map<ShapeType, std::string> GetAllShapeTypes();

    Qt::PenStyle GetStrokeStyleTypeByStrokeStyleName(const std::string& stroke_style_name) const;
    std::map<Qt::PenStyle, std::string> GetAllStrokeStyleTypes();

private:
    void Start();
    void CleanUp();

    void AddShapeType(ShapeType type, const std::string& name);
    void AddStrokeStyleType(Qt::PenStyle type, const std::string& name);

private:
    static ShapeManager* instance;

    DrawingWidget* drawing_widget = nullptr;

    std::vector<Shape*> shapes;

    std::map<ShapeType, std::string> shapes_types;

    std::map<Qt::PenStyle, std::string> stroke_styles;

};

#endif // SHAPEMANAGER_H
