#include "mainwindow.h"
#include <QApplication>

DataBase * DataBase::p_instance = nullptr;

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    DataBase::getInstance();
    /*settings s; // Temporarily commented out
    if(!s.isCheck())
    {
        QMessageBox box;
        box.setText("Autostart program is turned off. Turn it on in the settings, so as not to forget about birthdays");
        box.setWindowTitle("B-DAY | AUTORUN");
        box.setIcon(QMessageBox::Warning);
        box.exec();
    }
    s.~settings();*/
    MainWindow w;
    w.show();
    return a.exec();
}
