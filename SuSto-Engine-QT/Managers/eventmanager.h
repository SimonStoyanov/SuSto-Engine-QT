#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <functional>
#include <vector>
#include <map>

#include "Events/event.h"

class EventDelegate
{
    friend class EventManager;

private:
    void operator delete(void *) {}

public:
    EventDelegate(EventType e_type);

    void AddListener(const std::function<void(Event*)>& function);
    void RemoveListener(const std::function<void(Event*)>& function);

    void CallListeners(Event* ev);

private:
    std::vector<std::function<void(Event*)>> listeners;

    EventType event_type;
};

class EventManager
{
private:
    EventManager();
    void operator delete(void *) {}

public:
    static EventManager* Instance()
    {
        if(instance == nullptr)
        {
            instance = new EventManager();

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

    void Suscribe(const std::function<void(Event*)>& function, EventType e_type);
    void UnSuscribe(const std::function<void(Event*)>& function, EventType e_type);

    void SendEvent(Event*& ev);

private:
    void Start();
    void CleanUp();

    void DestroyAllEventDelegates();

private:
    static EventManager* instance;

    std::map<int, EventDelegate*> event_delegates;
};

#endif // EVENTMANAGER_H
