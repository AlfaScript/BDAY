#ifndef REMOVEDIALOG_H
#define REMOVEDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>

#include "settheader.h"
#include "forstr.h"
#include "database.h"

namespace Ui { class Removedialog; }

class Removedialog : public QDialog
{
    Q_OBJECT

public:
    explicit Removedialog(QWidget * parent = nullptr);
    ~Removedialog();

private slots:
    void on_backToMenu_clicked(void) noexcept;
    void on_removeButton_clicked(void) noexcept;

private:
    Ui::Removedialog * ui;
};

#endif // REMOVEDIALOG_H
