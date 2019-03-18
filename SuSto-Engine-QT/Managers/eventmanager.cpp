#include "eventmanager.h"
#include <iostream>
#include <memory>
#include <functional>

EventDelegate::EventDelegate(EventType e_type)
{
    event_type = e_type;
}

void EventDelegate::AddListener(const std::function<void(Event* ev)>& function)
{
    listeners.push_back(function);
}

void EventDelegate::RemoveListener(const std::function<void(Event*)>& function)
{
    for (std::vector<std::function<void(Event*)>>::iterator it = listeners.begin(); it != listeners.end(); ++it)
    {
        if ((*it).target_type() == function.target_type())
        {
            listeners.erase(it);
            break;
        }
    }
}

void EventDelegate::CallListeners(Event* ev)
{
    for (std::vector<std::function<void(Event*)>>::iterator it = listeners.begin(); it != listeners.end(); ++it)
    {
        if ((*it))
            (*it)(ev);
    }
}

// ---------------------------------------------------

EventManager* EventManager::instance = nullptr;

EventManager::EventManager()
{

}

void EventManager::Subscribe(const std::function<void (Event *)> &function, EventType e_type)
{
    Suscribe(std::bind(&EventManager::OnEvent, this, std::placeholders::_1), EventType::EVENT_NULL);

    EventDelegate* ed = event_delegates[e_type];

    if (ed == nullptr)
    {
        ed = new EventDelegate(e_type);

        event_delegates[e_type] = ed;
    }

    ed->AddListener(function);
}

void EventManager::UnSuscribe(const std::function<void (Event *)> &function, EventType e_type)
{
    EventDelegate* ed = event_delegates[e_type];

    if (ed != nullptr)
    {
        ed->RemoveListener(function);
    }
}

void EventManager::SendEvent(Event*& ev)
{
    if (ev != nullptr)
    {
        EventDelegate* ed = event_delegates[ev->GetType()];

        if (ed != nullptr)
        {
            ed->CallListeners(ev);
        }

        delete ev;
        ev = nullptr;
    }
}

void EventManager::OnEvent(Event *ev)
{

}

void EventManager::Start()
{

}

void EventManager::CleanUp()
{
    DestroyAllEventDelegates();
}

void EventManager::DestroyAllEventDelegates()
{
    for (std::map<int, EventDelegate*>::iterator it = event_delegates.begin(); it != event_delegates.end(); ++it)
    {
        delete((*it).second);
    }

    event_delegates.clear();
}
