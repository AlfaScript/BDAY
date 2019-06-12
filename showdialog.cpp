#include "showdialog.h"
#include "ui_showdialog.h"

Showdialog::Showdialog(QWidget * parent) : QDialog(parent), ui(new Ui::Showdialog)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView->setSortingEnabled(false);
    DataBase * db = DataBase::getInstance();
    db->getData(allDataFromDB);
    showAllList();
}

Showdialog::~Showdialog()
{
    delete ui;
}

void Showdialog::showAllList(void) noexcept
{
    QStandardItemModel * model = new QStandardItemModel;
    QStandardItem * item;
    model->setHorizontalHeaderLabels(horizontalHeader);
    uint8_t i = 0;
    for(const auto & line : allDataFromDB)
    {
        const QStringList tempStringList = line.split(" ");
        const QString firstName = tempStringList.at(0);
        const QString lastName = tempStringList.at(1);
        const uint8_t day = static_cast<uint8_t>(tempStringList.at(2).toUShort());
        const uint8_t month = static_cast<uint8_t>(tempStringList.at(3).toUShort());
        const uint16_t year = static_cast<uint16_t>(tempStringList.at(4).toUShort());

        item = new QStandardItem(firstName);
        model->setItem(i, 0, item);
        item = new QStandardItem(lastName);
        model->setItem(i, 1, item);
        item = new QStandardItem(QString::number(day));
        model->setItem(i, 2, item);
        item = new QStandardItem(QString::number(month));
        model->setItem(i, 3, item);
        item = new QStandardItem(QString::number(year));
        model->setItem(i, 4, item);
        ++i;
    }
    setTableView(*model);
}

void Showdialog::on_radioButton_clicked(void) noexcept
{
    showAllList();
}

void Showdialog::on_radioButton_2_clicked(void) noexcept
{
    QStandardItemModel * model = new QStandardItemModel;
    QStandardItem * item;
    model->setHorizontalHeaderLabels(horizontalHeader);
    uint8_t i = 0;
    const uint8_t currentMonth = static_cast<uint8_t>(QDate::currentDate().month());
    for(const auto & line : allDataFromDB)
    {
        const QStringList tempStringList = line.split(" ");
        const uint8_t month = static_cast<uint8_t>(tempStringList.at(3).toUShort());
        if(month == currentMonth)
        {
            const QString firstName = tempStringList.at(0);
            const QString lastName = tempStringList.at(1);
            const uint8_t day = static_cast<uint8_t>(tempStringList.at(2).toUShort());
            const uint16_t year = static_cast<uint16_t>(tempStringList.at(4).toUShort());

            item = new QStandardItem(firstName);
            model->setItem(i, 0, item);
            item = new QStandardItem(lastName);
            model->setItem(i, 1, item);
            item = new QStandardItem(QString::number(day));
            model->setItem(i, 2, item);
            item = new QStandardItem(QString::number(month));
            model->setItem(i, 3, item);
            item = new QStandardItem(QString::number(year));
            model->setItem(i, 4, item);
            ++i;
        }
    }
    setTableView(*model);
}

void Showdialog::on_radioButton_3_clicked(void) noexcept
{
    QStandardItemModel * model = new QStandardItemModel;
    QStandardItem * item;
    model->setHorizontalHeaderLabels(horizontalHeader);
    uint8_t i = 0;
    const uint8_t currentDay = static_cast<uint8_t>(QDate::currentDate().day());
    const uint8_t currentMonth = static_cast<uint8_t>(QDate::currentDate().month());
    for(const auto & line : allDataFromDB)
    {
        const QStringList tempStringList = line.split(" ");
        const uint8_t day = static_cast<uint8_t>(tempStringList.at(2).toUShort());
        const uint8_t month = static_cast<uint8_t>(tempStringList.at(3).toUShort());
        if(((month == currentMonth) && (day >= currentDay))
                || (month > currentMonth))
        {
            const QString firstName = tempStringList.at(0);
            const QString lastName = tempStringList.at(1);
            const uint16_t year = static_cast<uint16_t>(tempStringList.at(4).toUShort());

            item = new QStandardItem(firstName);
            model->setItem(i, 0, item);
            item = new QStandardItem(lastName);
            model->setItem(i, 1, item);
            item = new QStandardItem(QString::number(day));
            model->setItem(i, 2, item);
            item = new QStandardItem(QString::number(month));
            model->setItem(i, 3, item);
            item = new QStandardItem(QString::number(year));
            model->setItem(i, 4, item);
            ++i;
        }
    }
    setTableView(*model);
}

void Showdialog::setTableView(QAbstractItemModel & model) noexcept
{
    ui->tableView->setModel(&model);
    ui->tableView->show();
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
}
