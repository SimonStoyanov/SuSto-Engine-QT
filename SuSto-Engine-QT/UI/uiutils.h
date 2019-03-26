#ifndef UIUTILS_H
#define UIUTILS_H

#include <QObject>
#include "QLayout"

class QLayout;

class UIUtils
{
public:
    UIUtils();

    static void RemoveWidgetsFromLayout(QLayout* layout);
};

#endif // UIUTILS_H
