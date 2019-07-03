#include "mainwindow.h"
#include <QApplication>

std::shared_ptr<DataBase> DataBase::p_instance;

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    DataBase::getInstance();
    MainWindow w;
    w.show();
    return a.exec();
}
