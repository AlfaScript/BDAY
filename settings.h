#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QCoreApplication>
#include <QStandardPaths>

#include "settheader.h"
#include "database.h"

namespace Ui { class settings; }

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget * parent = nullptr);
    ~settings();
    bool isCheck(void) const noexcept;

private slots:
    void on_okButton_clicked(void) noexcept;
    void on_convButton_clicked(void) noexcept;
    void on_aboutButton_clicked(void) noexcept;
    void on_checkBox_stateChanged(int) noexcept;

private:
    Ui::settings * ui;
};

#endif // SETTINGS_H
