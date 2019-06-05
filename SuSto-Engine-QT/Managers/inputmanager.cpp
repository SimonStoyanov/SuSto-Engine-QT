#include "inputmanager.h"
#include "qevent.h"
#include "globals.h"
#include "QCursor"

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

bool InputManager::MouseButtonDown(Qt::MouseButton button)
{
    bool ret = false;

    for(std::vector<Qt::MouseButton>::iterator it = mouse_buttons_down.begin(); it != mouse_buttons_down.end(); ++it)
    {
        if((*it) == button)
        {
            ret = true;

            break;
        }
    }

    return ret;
}

bool InputManager::MouseButtonRepeat(Qt::MouseButton button)
{
    bool ret = false;

    for(std::vector<Qt::MouseButton>::iterator it = mouse_buttons_repeat.begin(); it != mouse_buttons_repeat.end(); ++it)
    {
        if((*it) == button)
        {
            ret = true;

            break;
        }
    }

    return ret;
}

bool InputManager::MouseButtonUp(Qt::MouseButton button)
{
    bool ret = false;

    for(std::vector<Qt::MouseButton>::iterator it = mouse_buttons_up.begin(); it != mouse_buttons_up.end(); ++it)
    {
        if((*it) == button)
        {
            ret = true;

            break;
        }
    }

    return ret;
}

float2 InputManager::MouseMovement()
{
    return mouse_pos - last_mouse_pos;
}

void InputManager::Start()
{

}

void InputManager::Update()
{
   UpdateKeysStates();
   UpdateMouseButtonsStates();
   UpdateMousePosition();
}

void InputManager::CleanUp()
{
    can_use_mouse_input = false;
}

bool InputManager::eventFilter(QObject *obj, QEvent *event)
{
    bool ret = false;

    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* ke = static_cast<QKeyEvent*>(event);

        Qt::Key curr_key =  static_cast<Qt::Key>(ke->key());

        keys_to_check[curr_key] = InputState::PRESS;
    }

    if (event->type() == QEvent::KeyRelease)
    {
        QKeyEvent* ke = static_cast<QKeyEvent*>(event);

        Qt::Key curr_key =  static_cast<Qt::Key>(ke->key());

        keys_to_check[curr_key] = InputState::RELEASE;
    }

    if(can_use_mouse_input)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* me = static_cast<QMouseEvent*>(event);

            Qt::MouseButton curr_button =  static_cast<Qt::MouseButton>(me->button());

            mouse_buttons_to_check[curr_button] = InputState::PRESS;
        }

        if(event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent* me = static_cast<QMouseEvent*>(event);

            Qt::MouseButton curr_button =  static_cast<Qt::MouseButton>(me->button());

            mouse_buttons_to_check[curr_button] = InputState::RELEASE;
        }
    }

    return ret;
}

void InputManager::UpdateKeysStates()
{
    for(std::vector<Qt::Key>::iterator kit = keys_down.begin(); kit != keys_down.end(); ++kit)
    {
        keys_repeat.push_back((*kit));
    }

    keys_down.clear();

    keys_up.clear();

    for(std::map<Qt::Key, InputState>::iterator it = keys_to_check.begin(); it != keys_to_check.end(); ++it)
    {
        switch ((*it).second)
        {
            case InputState::PRESS:
            {
                if(!KeyDown((*it).first) && !KeyRepeat((*it).first))
                {
                    keys_down.push_back(((*it).first));
                }

                break;
            }

            case InputState::RELEASE:
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

    keys_to_check.clear();
}

void InputManager::UpdateMouseButtonsStates()
{
    for(std::vector<Qt::MouseButton>::iterator kit = mouse_buttons_down.begin(); kit != mouse_buttons_down.end(); ++kit)
    {
        mouse_buttons_repeat.push_back((*kit));
    }

    mouse_buttons_down.clear();

    mouse_buttons_up.clear();

    for(std::map<Qt::MouseButton, InputState>::iterator it = mouse_buttons_to_check.begin(); it != mouse_buttons_to_check.end(); ++it)
    {
        switch ((*it).second)
        {
            case InputState::PRESS:
            {
                if(!MouseButtonDown((*it).first) && !MouseButtonRepeat((*it).first))
                {
                    mouse_buttons_down.push_back(((*it).first));
                }

                break;
            }

            case InputState::RELEASE:
            {
                if(MouseButtonRepeat((*it).first) && !MouseButtonUp((*it).first))
                {
                    for(std::vector<Qt::MouseButton>::iterator kit = mouse_buttons_repeat.begin(); kit != mouse_buttons_repeat.end(); ++kit)
                    {
                        if((*kit) == (*it).first)
                        {
                            mouse_buttons_repeat.erase(kit);

                            break;
                        }
                    }
                }

                break;
            }
        }
    }

    mouse_buttons_to_check.clear();
}

void InputManager::UpdateMousePosition()
{
    last_mouse_pos = mouse_pos;

    QPoint mouseLoc = QCursor::pos();
    mouse_pos = float2(mouseLoc.x(), mouseLoc.y());
}
