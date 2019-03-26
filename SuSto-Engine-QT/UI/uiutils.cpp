#include "UI/uiutils.h"
#include "qwidget.h"
#include "qlayout.h"

UIUtils::UIUtils()
{

}

void UIUtils::RemoveWidgetsFromLayout(QLayout* layout)
{
    if(layout != nullptr)
    {
        std::vector<QLayout*> to_check;

        to_check.push_back(layout);

        while(to_check.size() > 0)
        {
            QLayout* curr_layout = *to_check.begin();

            QLayoutItem* item = curr_layout->takeAt(0);

            while(item != nullptr)
            {
                curr_layout->removeItem(item);

                if(item->widget() != nullptr)
                {
                    item->widget()->setParent(nullptr);
                }

                else if(item->layout() != nullptr)
                {
                    to_check.push_back(item->layout());
                    item->layout()->setParent(nullptr);
                }

                layout->removeItem(item);

                item = curr_layout->takeAt(0);
            }

            to_check.erase(to_check.begin());
        }
    }
}
