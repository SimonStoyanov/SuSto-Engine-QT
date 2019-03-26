#ifndef SHAPEMANAGER_H
#define SHAPEMANAGER_H

#include <vector>

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

    Shape* CreateShape(ShapeType type);
    void DestroyShape(Shape*& sh);
    std::vector<Shape*> GetShapes() const;

    ShapeType GetShapeTypeByShapeName(const std::string& shape_name) const;
    std::map<ShapeType, std::string> GetAllShapeTypes();


private:
    void Start();
    void CleanUp();

    void AddShapeType(ShapeType type, const std::string& name);

private:
    static ShapeManager* instance;

    std::vector<Shape*> shapes;

    std::map<ShapeType, std::string> shapes_types;

};

#endif // SHAPEMANAGER_H
