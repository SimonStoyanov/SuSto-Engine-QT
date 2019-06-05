#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <qobject.h>
#include "3rdParty/MathGeoLib/Math/float2.h"

enum InputState
{
    PRESS,
    RELEASE,
};

class InputManager : public QObject
{
    friend class AppManager;

private:
    InputManager();
    void operator delete(void *) {}

public:
    static InputManager* Instance()
    {
        if(instance == nullptr)
        {
            instance = new InputManager();
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

public:
    bool KeyDown(Qt::Key key);
    bool KeyRepeat(Qt::Key key);
    bool KeyUp(Qt::Key key);

    bool MouseButtonDown(Qt::MouseButton button);
    bool MouseButtonRepeat(Qt::MouseButton button);
    bool MouseButtonUp(Qt::MouseButton button);

    float2 MouseMovement();

private:
    void Start();
    void Update();
    void CleanUp();

    bool eventFilter(QObject * obj, QEvent *event);

    void UpdateKeysStates();
    void UpdateMouseButtonsStates();
    void UpdateMousePosition();

private:
    static InputManager* instance;

    std::map<Qt::Key, InputState> keys_to_check;
    std::map<Qt::MouseButton, InputState> mouse_buttons_to_check;

    std::vector<Qt::Key> keys_down;
    std::vector<Qt::Key> keys_repeat;
    std::vector<Qt::Key> keys_up;

    std::vector<Qt::MouseButton> mouse_buttons_down;
    std::vector<Qt::MouseButton> mouse_buttons_repeat;
    std::vector<Qt::MouseButton> mouse_buttons_up;

    float2 mouse_pos = float2::zero;
    float2 last_mouse_pos = float2::zero;

    bool can_use_mouse_input = true;
};

#endif // INPUTMANAGER_H
