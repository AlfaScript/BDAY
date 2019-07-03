#include "database.h"

DataBase::DataBase(void)
{
    checkAndCreatingPathToDB();
    if(QFile(SETT::pathToDB).exists())
    {
        if(QFile fileDataBase(SETT::pathToDB); !fileDataBase.open(QIODevice::ReadOnly) && !fileDataBase.isOpen())
            showMessageBox(QMessageBox::Critical, "B-DAY | ERROR", "Error #2: the database file can not be read\n"
                                                                   "Our advice: try manually open the database file");
        else
        {
            while (!fileDataBase.atEnd())
                cacheData.push_back(fileDataBase.readLine());
            showTodaysBD();
            showTommorowBD();
        }
    }
}

std::shared_ptr<DataBase> DataBase::getInstance(void) noexcept
{
    if (!p_instance)
       p_instance = std::make_shared<DataBase>();
    return p_instance;
}

void DataBase::DestroyInstance(void) noexcept
{
    // delete p_instance;
    p_instance = nullptr;
}

void DataBase::addPerson(QString && firstName, QString && lastName, QString && data) noexcept
{
    const QString stringToWrite = firstName + " " + lastName + " " + data + "\r\n";
    QFile fileDataBase(SETT::pathToDB);
    if(!fileDataBase.exists())
    {
        if(!fileDataBase.open(QIODevice::WriteOnly) && !fileDataBase.isOpen())
        {
            showMessageBox(QMessageBox::Critical, "B-DAY | ERROR", "Error #1: the database file can not be created");
            return;
        }
    }
    else
    {
        if(!fileDataBase.open(QIODevice::Append) && !fileDataBase.isOpen())
        {
            showMessageBox(QMessageBox::Critical, "B-DAY | ERROR", "Error #1: the database file can not be opened");
            return;
        }
    }
    fileDataBase.write(stringToWrite.toStdString().c_str());
    cacheData.push_back(stringToWrite);
    showMessageBox(QMessageBox::Information, "B-DAY | ADD", "The person was added successfully");
}

bool DataBase::removePerson(QString && firstNameRemove, QString && lastNameRemove) noexcept
{
    uint8_t removeIndex = 0;
    for(const auto & line : cacheData)
    {
        const QStringList lineOfDataBase = line.split(" ");
        const QString firstNameDB = lineOfDataBase.at(0);
        const QString lastNameDB = lineOfDataBase.at(1);
        if(lastNameRemove == lastNameDB)
        {
            if(firstNameRemove == firstNameDB)
                break;
        }
        ++removeIndex;
    }

    if(removeIndex != cacheData.size())
    {
        cacheData.removeAt(removeIndex);
        return true;
    }
    return false;
}

void DataBase::updateDataBaseFile(void) const noexcept
{
    if(QFile fileDataBase(SETT::pathToDB); fileDataBase.exists())
    {
        if(!fileDataBase.open(QIODevice::WriteOnly | QIODevice::Truncate) && !fileDataBase.isOpen())
            showMessageBox(QMessageBox::Critical, "B-DAY | ERROR", "Error #1: the database file can not be opened");
        else
        {
            for(const auto & line : cacheData)
                fileDataBase.write(line.toStdString().c_str());
        }
    }
}

void DataBase::getData(QList<QString> & list) const noexcept
{
    for(const auto & line : cacheData)
        list.push_back(line);
}

void DataBase::importDatabase(const QString & fileName) noexcept
{
    if(QFile importFile(fileName); !importFile.open(QIODevice::ReadOnly) && !importFile.isOpen())
        showMessageBox(QMessageBox::Critical, "B-DAY | ERROR", "Error #2: the file with import database can not be read\n"
                                                               "Our advice: try to open the database file");
    else
    {
        if(QFile fileDataBase(SETT::pathToDB); !fileDataBase.open(QIODevice::Append) && !fileDataBase.isOpen())
            showMessageBox(QMessageBox::Critical, "B-DAY | ERROR", "Error #1: the database file can not be opened");
        else
        {
            const auto iteratorOfEnd = cacheData.end();
            while(!importFile.atEnd())
            {
                const QString tempStrImport = importFile.readLine();
                if(std::find(cacheData.begin(), cacheData.end(), tempStrImport) == iteratorOfEnd)
                {
                    cacheData.push_back(tempStrImport);
                    fileDataBase.write(tempStrImport.toStdString().c_str());
                }
            }
        }
    }
}

void DataBase::checkAndCreatingPathToDB(void) noexcept
{
    if(!QDir(SETT::APPDATALOCATION + "\\" + SETT::COMPANY_NAME).exists() ||
            !QDir(SETT::APPDATALOCATION + "\\" + SETT::COMPANY_NAME + "\\" + SETT::APPLICATION_NAME).exists())
        QDir().mkpath(SETT::APPDATALOCATION + "\\" + SETT::COMPANY_NAME + "\\" + SETT::APPLICATION_NAME);
}

void DataBase::showMessageBox(QMessageBox::Icon icon, const QString & titleOfMessageBox, const QString & textOfMessageBox) const noexcept
{
    QMessageBox messageBox;
    messageBox.setWindowTitle(titleOfMessageBox);
    messageBox.setIcon(icon);
    messageBox.setText(textOfMessageBox);
    messageBox.setButtonText(0, "OKAY");
    messageBox.exec();
}

void DataBase::showTodaysBD(void) const noexcept
{
    const QDate currentDate(QDate::currentDate().year(), QDate::currentDate().month(), QDate::currentDate().day());

    for(auto it = cacheData.begin(); it != cacheData.end(); ++it)
    {
        const QStringList tempStrList = it->split(" ");
        const QDate dateOfBD(tempStrList.at(4).toInt(), tempStrList.at(3).toInt(), tempStrList.at(2).toInt());
        if((dateOfBD.day() == currentDate.day()) && (dateOfBD.month() == currentDate.month()))
        {
            const QString firstName = tempStrList.at(0);
            const QString lastName = tempStrList.at(1);
            const uint8_t yearsOld = static_cast<uint8_t>(currentDate.year() - dateOfBD.year());
            showMessageBox(QMessageBox::Information, "TODAY BIRTH DAY OF PERSON", "The birth day of " + firstName + " " + lastName
                           + " (" + QString::number(yearsOld) + " years old).");
        }
    }
}

void DataBase::showTommorowBD(void) const noexcept
{
    const QDate currentDate(QDate::currentDate().year(), QDate::currentDate().month(), QDate::currentDate().day());

    for(auto it = cacheData.begin(); it != cacheData.end(); ++it)
    {
        const QStringList tempStrList = it->split(" ");
        const QDate dateOfBD(tempStrList.at(4).toInt(), tempStrList.at(3).toInt(), tempStrList.at(2).toInt());
        if(currentDate.addDays(1) == dateOfBD)
        {
            const QString firstName = tempStrList.at(0);
            const QString lastName = tempStrList.at(1);
            const uint8_t yearsOld = static_cast<uint8_t>(currentDate.year() - dateOfBD.year());
            showMessageBox(QMessageBox::Information, "TOMORROW BIRTH DAY OF PERSON", "Tomorrow is the birthday of " + firstName + " " + lastName
                           + " (" + QString::number(yearsOld) + " years old).");
        }
    }
}
