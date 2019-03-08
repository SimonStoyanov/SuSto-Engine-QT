#ifndef EVENT_H
#define EVENT_H

enum EventType
{
    EVENT_NULL,
};

class Event
{
public:
    Event(EventType t);

    EventType GetType() const;

private:
    EventType ev_type = EventType::EVENT_NULL;
};

#endif // EVENT_H