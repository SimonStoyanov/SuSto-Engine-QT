#include "component.h"
#include "entity.h"

#include <QTextStream>

Component::Component()
{

}

Component::Component(component_type type_, Entity owner_)
{
    // Used to log in console
    QTextStream out(stdout);

    switch (type_)
    {
        case component_type::COMPONENT_TRANSFORM:
        {
            out << "Component -Transform- created" << endl;
        }
        break;
        case component_type::COMPONENT_SHAPE_RENDERER:
        {
            out << "Component -Shape Renderer- created" << endl;
        }
        break;
        case component_type::COMPONENT_NULL:
        {
            out << "Component of type null created" << endl;
        }
        break;
    }
}
