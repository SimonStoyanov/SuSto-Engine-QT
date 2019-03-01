#include "event.h"

Event::Event(EventType t)
{
    ev_type = t;
}

EventType Event::GetType() const
{
    return ev_type;
}
