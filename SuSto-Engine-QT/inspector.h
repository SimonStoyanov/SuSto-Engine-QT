#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

class Component;

namespace Ui {
class Inspector;
class Transform;
}

class Entity;
class MainWindow;
class Event;

class Inspector : public QWidget
{
    Q_OBJECT

public:
    explicit Inspector(MainWindow* mainwindow_, QWidget *parent = nullptr);
    ~Inspector();

public slots:
    void UpdateUI();

private slots:
    void EntityNameChanged(const QString& str);
    void AddComponentButton();
    void RemoveComponentButton(Component* comp);
    void AddComponentSelected(const std::string& component);

private:
    void OnEvent(Event *event);

private:
    MainWindow* mainwindow = nullptr;
    Ui::Inspector *ui = nullptr;

    bool update_ui = true;
};

#endif // INSPECTOR_H
