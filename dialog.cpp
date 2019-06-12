#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget * parent) : QDialog(parent), ui(new Ui::Dialog), currentDate(QDate::currentDate())
{
    ui->setupUi(this);
    ui->bDate->setMaximumDate(currentDate);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_backToMenu_clicked(void) noexcept
{
    this->close();
}

void Dialog::on_pushButton_clicked(void) noexcept
{
    QString firstName = ui->firstName->text();
    QString lastName = ui->lastName->text();
    if(!forStr::reviewStr(firstName) || !forStr::reviewStr(lastName))
        QMessageBox::critical(this, "B-DAY | ERROR", "Error #3: the string is empty or contains prohibited characters\n"
                                             "Our advice: enter only letters", "OKAY");
    else
    {
        DataBase * db = DataBase::getInstance();
        db->addPerson(std::move(firstName), std::move(lastName), ui->bDate->date().toString("d M yyyy"));
    }
}
