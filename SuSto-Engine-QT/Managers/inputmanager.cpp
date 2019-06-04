#include "inputmanager.h"
#include "qevent.h"
#include "globals.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager()
{

}

bool InputManager::KeyDown(Qt::Key key)
{
    bool ret = false;

    for(std::vector<Qt::Key>::iterator it = keys_down.begin(); it != keys_down.end(); ++it)
    {
        if((*it) == key)
        {
            ret = true;

            break;
        }
    }

    return ret;
}

bool InputManager::KeyRepeat(Qt::Key key)
{
    bool ret = false;

    for(std::vector<Qt::Key>::iterator it = keys_repeat.begin(); it != keys_repeat.end(); ++it)
    {
        if((*it) == key)
        {
            ret = true;

            break;
        }
    }

    return ret;
}

bool InputManager::KeyUp(Qt::Key key)
{
    bool ret = false;

    for(std::vector<Qt::Key>::iterator it = keys_up.begin(); it != keys_up.end(); ++it)
    {
        if((*it) == key)
        {
            ret = true;

            break;
        }
    }

    return ret;
}

void InputManager::Start()
{

}

void InputManager::Update()
{
    for(std::vector<Qt::Key>::iterator kit = keys_down.begin(); kit != keys_down.end(); ++kit)
    {
        keys_repeat.push_back((*kit));
    }

    keys_down.clear();

    keys_up.clear();

    for(std::map<Qt::Key, KeyState>::iterator it = keys_to_check.begin(); it != keys_to_check.end(); ++it)
    {
        switch ((*it).second)
        {
            case KeyState::PRESS:
            {
                if(!KeyDown((*it).first) && !KeyRepeat((*it).first))
                {
                    keys_down.push_back(((*it).first));
                }

                break;
            }

            case KeyState::RELEASE:
            {
                if(KeyRepeat((*it).first) && !KeyUp((*it).first))
                {
                    for(std::vector<Qt::Key>::iterator kit = keys_repeat.begin(); kit != keys_repeat.end(); ++kit)
                    {
                        if((*kit) == (*it).first)
                        {
                            keys_repeat.erase(kit);

                            break;
                        }
                    }
                }

                break;
            }
        }
    }

    SPOOKYLOG(std::to_string(keys_repeat.size()));


    keys_to_check.clear();
}

void InputManager::CleanUp()
{

}

bool InputManager::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);

        Qt::Key curr_key =  static_cast<Qt::Key>(ke->key());

        keys_to_check[curr_key] = KeyState::PRESS;
    }

    if (event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);

        Qt::Key curr_key =  static_cast<Qt::Key>(ke->key());

        keys_to_check[curr_key] = KeyState::RELEASE;
    }

    return false;
}
