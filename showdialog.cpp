#include "showdialog.h"
#include "ui_showdialog.h"

Showdialog::Showdialog(QWidget * parent) : QDialog(parent), ui(new Ui::Showdialog)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView->setSortingEnabled(false);
    std::shared_ptr<DataBase> db(DataBase::getInstance());
    db->getData(allDataFromDB);
    showAllList();
}

Showdialog::~Showdialog()
{
    delete ui;
}

void Showdialog::showAllList(void) noexcept
{
    // std::unique_ptr<QStandardItemModel> model(new QStandardItemModel);
    QStandardItemModel * model = new QStandardItemModel;
    QStandardItem * item;
    model->setHorizontalHeaderLabels(horizontalHeader);
    uint8_t numberOfRows = 0;
    for(const auto & line : allDataFromDB)
    {
        const QStringList tempStringList = line.split(" ");
        const QString firstName = tempStringList.at(0);
        const QString lastName = tempStringList.at(1);
        const uint8_t day = static_cast<uint8_t>(tempStringList.at(2).toUShort());
        const uint8_t month = static_cast<uint8_t>(tempStringList.at(3).toUShort());
        const uint16_t year = static_cast<uint16_t>(tempStringList.at(4).toUShort());

        /*std::unique_ptr<QStandardItem> firstNamePtr(new QStandardItem(firstName));
        model->setItem(numberOfRows, 0, firstNamePtr.release());
        std::unique_ptr<QStandardItem> lastNamePtr(new QStandardItem(lastName));
        model->setItem(numberOfRows, 1, lastNamePtr.release());
        std::unique_ptr<QStandardItem> dayPtr(new QStandardItem(QString::number(day)));
        model->setItem(numberOfRows, 2, dayPtr.release());
        std::unique_ptr<QStandardItem> monthPtr(new QStandardItem(QString::number(month)));
        model->setItem(numberOfRows, 3, monthPtr.release());
        std::unique_ptr<QStandardItem> yearPtr(new QStandardItem(QString::number(year)));
        model->setItem(numberOfRows, 4, yearPtr.release());*/

        item = new QStandardItem(firstName);
        model->setItem(numberOfRows, 0, item);
        item = new QStandardItem(lastName);
        model->setItem(numberOfRows, 1, item);
        item = new QStandardItem(QString::number(day));
        model->setItem(numberOfRows, 2, item);
        item = new QStandardItem(QString::number(month));
        model->setItem(numberOfRows, 3, item);
        item = new QStandardItem(QString::number(year));
        model->setItem(numberOfRows, 4, item);
        ++numberOfRows;
    }
    setTableView(*model);
}

void Showdialog::on_radioButton_clicked(void) noexcept
{
    showAllList();
}

void Showdialog::on_radioButton_2_clicked(void) noexcept
{
    // std::unique_ptr<QStandardItemModel> model(new QStandardItemModel);
    QStandardItemModel * model = new QStandardItemModel;
    QStandardItem * item;
    model->setHorizontalHeaderLabels(horizontalHeader);
    uint8_t numberOfRows = 0;
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
            model->setItem(numberOfRows, 0, item);
            item = new QStandardItem(lastName);
            model->setItem(numberOfRows, 1, item);
            item = new QStandardItem(QString::number(day));
            model->setItem(numberOfRows, 2, item);
            item = new QStandardItem(QString::number(month));
            model->setItem(numberOfRows, 3, item);
            item = new QStandardItem(QString::number(year));
            model->setItem(numberOfRows, 4, item);
            ++numberOfRows;
        }
    }
    setTableView(*model);
}

void Showdialog::on_radioButton_3_clicked(void) noexcept
{
    // std::unique_ptr<QStandardItemModel> model(new QStandardItemModel);
    QStandardItemModel * model = new QStandardItemModel;
    QStandardItem * item;
    model->setHorizontalHeaderLabels(horizontalHeader);
    uint8_t numberOfRows = 0;
    const QDate currentDate(QDate::currentDate().year(), QDate::currentDate().month(), QDate::currentDate().day());
    for(const auto & line : allDataFromDB)
    {
        const QStringList tempStringList = line.split(" ");
        const QDate dateOfBD(tempStringList.at(4).toInt(), tempStringList.at(3).toInt(), tempStringList.at(2).toInt());
        if(((dateOfBD.month() == currentDate.month()) && (dateOfBD.day() >= currentDate.day()))
                || (dateOfBD.month() > currentDate.month()))
        {
            const QString firstName = tempStringList.at(0);
            const QString lastName = tempStringList.at(1);

            item = new QStandardItem(firstName);
            model->setItem(numberOfRows, 0, item);
            item = new QStandardItem(lastName);
            model->setItem(numberOfRows, 1, item);
            item = new QStandardItem(QString::number(dateOfBD.day()));
            model->setItem(numberOfRows, 2, item);
            item = new QStandardItem(QString::number(dateOfBD.month()));
            model->setItem(numberOfRows, 3, item);
            item = new QStandardItem(QString::number(dateOfBD.year()));
            model->setItem(numberOfRows, 4, item);
            ++numberOfRows;
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
