#ifndef C_TRANSFORM_H
#define C_TRANSFORM_H

#include "component.h"

class C_Transform : public Component
{
public:
    C_Transform(Entity* owner);
    ~C_Transform();
};

#endif // C_TRANSFORM_H
