#ifndef FLOATINGCONTEXT_H
#define FLOATINGCONTEXT_H

#include <QDialog>
#include <vector>
#include <QCloseEvent>

class QSignalMapper;

namespace Ui {
class floatingcontext;
}

class FloatingContext : public QDialog
{
    Q_OBJECT

signals:
    void dialogClosed(std::string);

public:
     explicit FloatingContext(QWidget *parent);
    ~FloatingContext();

    void reject() override;

    void UpdateUI();

    void SetDescription(const std::string& description);
    void SetContent(const std::vector<std::string>& content);

private slots:
    void ContentPressed(const std::string& content);

private:
    Ui::floatingcontext *ui;

    std::string description = "Description";
    std::vector<std::string> content;

    std::string content_selected = "";
};


#endif // FLOATINGCONTEXT_H
