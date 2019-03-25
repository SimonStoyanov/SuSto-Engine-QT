#ifndef SELECTENTITYCHANGE_H
#define SELECTENTITYCHANGE_H

#include "Events/event.h"

class Entity;

class SelectEntityChange : public Event
{
    friend class EventManager;

public:
    SelectEntityChange(Entity* entity);

private:
    Entity* GetEntity() const;

private:
    Entity* entity = nullptr;
};

#endif // SELECTENTITYCHANGE_H
