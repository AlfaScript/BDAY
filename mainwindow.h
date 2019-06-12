#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QWidget>
#include <QMessageBox>
#include <QPointer>
#include <future>

/*--- FORMS (Windows) ---*/
#include "dialog.h"
#include "removedialog.h"
#include "showdialog.h"
#include "settings.h"

/*--- HEADERS ---*/
#include "settheader.h"
#include "database.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonAdd_clicked(void) noexcept;
    void on_buttonRemove_clicked(void) noexcept;
    void on_buttonShow_clicked(void) noexcept;
    void on_buttonSettings_clicked(void) noexcept;

private:
    Ui::MainWindow * ui;
    void mouseMoveEvent(const QMouseEvent * event) noexcept;
};

#endif // MAINWINDOW_H
