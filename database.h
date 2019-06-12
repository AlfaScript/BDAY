#ifndef DATABASE_H
#define DATABASE_H

#include <QDir>
#include <QList>
#include <QMessageBox>
#include <QDate>
#include "settheader.h"

class DataBase
{
public:
    static DataBase * getInstance(void) noexcept;
    static void DestroyInstance(void) noexcept;

    DataBase(void);
    ~DataBase() { }
    DataBase(const DataBase &) = delete;
    DataBase & operator=(const DataBase &) = delete;
    DataBase(DataBase && other) = delete;

    void addPerson(QString && firstName, QString && lastName, QString && data) noexcept;
    bool removePerson(QString &&, QString &&) noexcept;
    void updateDataBaseFile(void) const noexcept;
    void getData(QList<QString> &) const noexcept;
    void importDatabase(const QString &) noexcept;

private:
    static DataBase * p_instance;
    QList<QString> cacheData;
};

#endif // DATABASE_H
