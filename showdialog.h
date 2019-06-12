#ifndef SHOWDIALOG_H
#define SHOWDIALOG_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QStringList>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDate>

#include "settheader.h"
#include "database.h"

namespace Ui { class Showdialog; }

class Showdialog : public QDialog
{
    Q_OBJECT

public:
    explicit Showdialog(QWidget * parent = nullptr);
    ~Showdialog();

private slots:
    void on_radioButton_clicked(void) noexcept;
    void on_radioButton_2_clicked(void) noexcept;
    void on_radioButton_3_clicked(void) noexcept;

private:
    Ui::Showdialog * ui;

    void showAllList(void) noexcept;
    void setTableView(QAbstractItemModel &) noexcept;

    QList<QString> allDataFromDB;
    const QStringList horizontalHeader{"NAME", "SURNAME", "DAY", "MONTH", "YEAR"};
};

#endif // SHOWDIALOG_H
