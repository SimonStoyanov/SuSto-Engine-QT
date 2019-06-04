#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <qobject.h>

enum KeyState
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

private:
    void Start();
    void Update();
    void CleanUp();

    bool eventFilter(QObject * obj, QEvent *event);

private:
    static InputManager* instance;

    std::map<Qt::Key, KeyState> keys_to_check;

    std::vector<Qt::Key> keys_down;
    std::vector<Qt::Key> keys_repeat;
    std::vector<Qt::Key> keys_up;
};

#endif // INPUTMANAGER_H
