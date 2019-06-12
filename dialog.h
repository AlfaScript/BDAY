#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QDir>

#include "settheader.h"
#include "forstr.h"
#include "database.h"

namespace Ui { class Dialog; }

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget * parent = nullptr);
    ~Dialog();

private slots:
    void on_backToMenu_clicked(void) noexcept;
    void on_pushButton_clicked(void) noexcept;

private:
    Ui::Dialog * ui;
    const QDate currentDate;
};

#endif // DIALOG_H
