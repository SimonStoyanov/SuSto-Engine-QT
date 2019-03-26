#include "floatingcontext.h"
#include "ui_floatingcontext.h"
#include "QPushButton"
#include "QSignalMapper"
#include "globals.h"

FloatingContext::FloatingContext(QWidget *parent) :
    QDialog(nullptr),
    ui(new Ui::floatingcontext)
{
    ui->setupUi(this);
}

FloatingContext::~FloatingContext()
{
    delete ui;
}

void FloatingContext::reject()
{
    SPOOKYLOG("CLOSE");
    emit dialogClosed(content_selected);
    QDialog::reject();
}

void FloatingContext::UpdateUI()
{
    this->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint);
    this->setWindowModality(Qt::ApplicationModal);

    ui->descriptionLabel->setText(QString::fromStdString(description));

    RemoveAllContentWidgets();

    for(std::vector<std::string>::iterator it = content.begin(); it != content.end(); ++it)
    {
        QPushButton* button = new QPushButton();
        button->setText(QString::fromStdString((*it)));

        connect(button, &QPushButton::clicked, [this, button]() {ContentPressed(button->text().toStdString());});

        ui->verticalLayout->addWidget(button);
    }
}

void FloatingContext::SetDescription(const std::string &descr)
{
    description = descr;

    UpdateUI();
}

void FloatingContext::SetContent(const std::vector<std::string> &cont)
{
    content = cont;

    UpdateUI();
}

void FloatingContext::RemoveAllContentWidgets()
{
    QLayoutItem* item = ui->verticalLayout->takeAt(0);

    while(item != nullptr)
    {
        item->widget()->setParent(nullptr);

        ui->verticalLayout->removeItem(item);

        item = ui->verticalLayout->takeAt(0);
    }
}

void FloatingContext::ContentPressed(const std::string &content)
{
    content_selected = content;

    this->close();
}
