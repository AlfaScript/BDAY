#ifndef DATABASE_H
#define DATABASE_H

#include <QDir>
#include <QList>
#include <QMessageBox>
#include <QDate>
#include <memory>
#include <utility>
#include "settheader.h"

class DataBase
{
public:
    static std::shared_ptr<DataBase> getInstance(void) noexcept;
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
    void checkAndCreatingPathToDB(void) noexcept;
    void showMessageBox(QMessageBox::Icon, const QString &, const QString &) const noexcept;
    void showTodaysBD(void) const noexcept;
    void showTommorowBD(void) const noexcept;

    static std::shared_ptr<DataBase> p_instance;
    QList<QString> cacheData;
};

#endif // DATABASE_H
