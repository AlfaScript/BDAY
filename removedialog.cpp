#include "removedialog.h"
#include "ui_removedialog.h"

Removedialog::Removedialog(QWidget * parent) : QDialog(parent), ui(new Ui::Removedialog)
{
    ui->setupUi(this);
}

Removedialog::~Removedialog()
{
    delete ui;
}

void Removedialog::on_backToMenu_clicked(void) noexcept
{
    this->close();
}

void Removedialog::on_removeButton_clicked(void) noexcept
{
    QString firstName = ui->firstName->text();
    QString lastName = ui->lastName->text();
    if(!forStr::reviewStr(firstName) || !forStr::reviewStr(lastName))
        QMessageBox::critical(this, "B-DAY | ERROR", "Error #3: the string is empty or contains prohibited characters\n"
                                             "Our advice: enter only letters", "OKAY");
    else
    {
        DataBase * db = DataBase::getInstance();
        if(db->removePerson(std::move(firstName), std::move(lastName)))
        {
            db->updateDataBaseFile();
            QMessageBox::information(this, "B-DAY | REMOVE", "The person was removed successfully", "OKAY");
        }
        else
            QMessageBox::warning(this, "B-DAY | NOT FOUND", "The person was not found", "OKAY");
    }
    this->close();
}
