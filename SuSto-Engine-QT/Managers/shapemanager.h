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

private:
    void Start();
    void CleanUp();

private:
    static ShapeManager* instance;

    std::vector<Shape*> shapes;

};

#endif // SHAPEMANAGER_H
