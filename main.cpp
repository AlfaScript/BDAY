#include "mainwindow.h"
#include <QApplication>

DataBase * DataBase::p_instance = nullptr;

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    DataBase::getInstance();
    MainWindow w;
    w.show();
    return a.exec();
}
